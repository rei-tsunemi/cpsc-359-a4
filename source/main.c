#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "initGPIO.h"
#include <time.h>

#include "backgrounds.h"
#include "sprites.h"

#include "L.h"
#include "I.h"
#include "F.h"
#include "E.h"
#include "dot.h"
#include "V.h"
#include "T.h"
#include "M.h"

/*CPSC 359
 * PETER KUCHEL 30008687
 * REI TSUNEMI 30121202
 *
 * ASSIGNMENT 4
 *
 * */

#define CLK 11 // clock
#define LAT 9  // latch
#define DAT 10 // data

#define GPSET0 7  // set registers
#define GPCLR0 10 // clear registers
#define GPLEV0 13 // level registers

#define X_MAX 1920
#define Y_MAX 1056
#define BLOCKSIZE = 32

static int gridSize = 32;
static int baseSpeed = 55000;

static unsigned int *gpioPtr; // get global gpio pointer
static int globalButtons[16]; // to store the input value from the buttons / register sample buttons

// GPIO setup macros.
#define INP_GPIO(g) *(gpioPtr + ((g) / 10)) &= ~(7 << (((g) % 10) * 3)) // set input
#define OUT_GPIO(g) *(gpioPtr + ((g) / 10)) |= (1 << (((g) % 10) * 3))	// set output

/* Definitions */
typedef struct
{
	short int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

void Init_GPIO()
{
	INP_GPIO(CLK);
	OUT_GPIO(CLK); // init clock to output

	INP_GPIO(LAT);
	OUT_GPIO(LAT); // init latch to output

	INP_GPIO(DAT); // init data to input
}

void Write_Latch(int writeData)
{
	// if writing 1 to the latch pin
	if (writeData == 1)
	{
		gpioPtr[GPSET0] = 1 << LAT;
	}

	// else clear the pin
	else
	{
		gpioPtr[GPCLR0] = 1 << LAT;
	}
}

void Write_Clock(int writeData)
{
	// if writing 1 to the latch pin
	if (writeData == 1)
	{
		gpioPtr[GPSET0] = 1 << CLK;
	}
	// else clear the pin
	else
	{
		gpioPtr[GPCLR0] = 1 << CLK;
	}
}

int Read_Data()
{
	/*
	 * read the data in from the snes controller
	 * for the particular button being pressed
	 * 0 means it was pressed
	 * */
	return (gpioPtr[GPLEV0] >> DAT) & 1;
}

void Wait(unsigned int waitTime)
{
	delayMicroseconds(waitTime); // wait in microseconds
}

void Read_SNES()
{

	Write_Clock(1);		   // write 1 to the clock
	Write_Latch(1);		   // write 1 to the latch
	delayMicroseconds(12); // delayMicroseconds 12 micro seconds / signal to the SNES to sample buttons
	Write_Latch(0);		   // clear latch
	int i = 1;			   // start at button 1

	while (i <= 15) // start pulsing to read from SNES
	{
		delayMicroseconds(6); // wait 6 micro seconds
		Write_Clock(0);		  // falling edge
		delayMicroseconds(6); // wait 6 micro seconds
		// printf("okay here ");
		globalButtons[i] = Read_Data(); // read bit i
		Write_Clock(1);					// rising edge,new cycle
		i++;							// next button
	}
}

/*
	up down left right
	5  6    7    8
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getColour(int num)
{
	if (num == 1)
		return 0x00FF;
	else if (num == 0)
		return 0xFFFF;
	else // num is 2
		return 0x0000;
}

void checkCollision(int *x, int *y)
{
}

void checkGoal(int posX, int posY, int *x, int *y, int *status)
{
	if (((*x >= posX) && (*x <= posX + 5)) && ((*y >= posY) && (*y <= posY + 90)))
	{
		*status = 0;
	}
}

void getCartSpeed(int *speed, int *x, int *y, int bg[33][60])
{
	int colourPos = bg[*y / gridSize][*x / gridSize];
	if (colourPos != 2)
		// *speed = baseSpeed * 4;
		*speed = baseSpeed;
	else
		*speed = baseSpeed;
}

void determineButtonPressed(int i, int *x, int *y, int *status, int *speed)
{
	int mov = 32;
	if (i == 4)
		*status = 0;
	else if (i == 5)
	{
		if ((*y) == 64)
			(*y) = (*y);
		else
			(*y) -= mov;
	}
	else if (i == 6)
	{
		if ((*y) == 1024)
			(*y) = (*y);
		else
			(*y) += mov;
	}
	else if (i == 7)
	{
		if ((*x) == 0)
			(*x) = (*x);
		else
			(*x) -= mov;
	}
	else
	{
		if ((*x) == 1888)
			(*x) = (*x);
		else
			(*x) += mov;
	}
	delayMicroseconds(*speed);
}

void drawImage(int xD, int yD, int sizeX, int sizeY, Pixel *pixel, short int *image)
{
	int i = 0;
	for (int y = 0; y < sizeX; y++)
	{ // image height
		for (int x = 0; x < sizeY; x++)
		{ // image width
			pixel->color = image[i];
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);
			i++;
		}
	}
}

void drawBlock(int sizeX, int sizeY, int xD, int yD, int clr, Pixel *pixel)
{
	for (int y = 0; y < sizeY; y++) // draw height
	{
		for (int x = 0; x < sizeX; x++) // draw width
		{
			pixel->color = clr;
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);
		}
	}
}

void drawHeader()
{
	short int *life_Ptr[5];
	short int *level_Ptr[6];
	short int *time_Ptr[5];
	int i;
	int dim = 64;  // dimention of each alphabet
	int sx = 0;	   // starting position for LEVEL:
	int lx = 704;  // starting position for LIFE:
	int tx = 1472; // starting position for TIME:

	/* array storing all alphabet for level */
	life_Ptr[0] = (short int *)alp_L.pixel_data;
	life_Ptr[1] = (short int *)alp_I.pixel_data;
	life_Ptr[2] = (short int *)alp_F.pixel_data;
	life_Ptr[3] = (short int *)alp_E.pixel_data;
	life_Ptr[4] = (short int *)alp_colon.pixel_data;

	/* array storing all alphabet for life */
	level_Ptr[0] = (short int *)alp_L.pixel_data;
	level_Ptr[1] = (short int *)alp_E.pixel_data;
	level_Ptr[2] = (short int *)alp_V.pixel_data;
	level_Ptr[3] = (short int *)alp_E.pixel_data;
	level_Ptr[4] = (short int *)alp_L.pixel_data;
	level_Ptr[5] = (short int *)alp_colon.pixel_data;

	/* array storing all alphabet for time */
	time_Ptr[0] = (short int *)alp_T.pixel_data;
	time_Ptr[1] = (short int *)alp_I.pixel_data;
	time_Ptr[2] = (short int *)alp_M.pixel_data;
	time_Ptr[3] = (short int *)alp_E.pixel_data;
	time_Ptr[4] = (short int *)alp_colon.pixel_data;

	Pixel *pix;
	pix = malloc(sizeof(Pixel));

	for (i = 0; i < 6; i++)
	{
		drawImage(sx, 0, dim, dim, pix, level_Ptr[i]);
		sx += 64;
	}
	for (i = 0; i < 5; i++)
	{
		drawImage(lx, 0, dim, dim, pix, life_Ptr[i]);
		drawImage(tx, 0, dim, dim, pix, time_Ptr[i]);
		lx += 64;
		tx += 64;
	}

	free(pix);
}

void drawNewScene(int bg[33][60])
{
	int blockSize = 32;
	int xSize = 60;
	int ySize = 33;
	Pixel *scenePixel = malloc(sizeof(Pixel));
	int yOff, xOff;
	for (int y = 0; y < ySize; y++)
	{
		yOff = y * blockSize;
		for (int x = 0; x < xSize; x++)
		{
			xOff = x * blockSize;
			int colour = getColour(bg[y][x]);
			drawBlock(blockSize, blockSize, xOff, yOff, colour, scenePixel);
		}
	}
	free(scenePixel);
}

void repaint(int i, int xD, int yD, Pixel *pixel, int bg[33][60])
{
	int gridDim = 32;
	int xPaint = xD;
	int yPaint = yD;
	int colour;

	if (i == 5)
	{
		yPaint += gridDim;
	}
	else if (i == 6)
	{
		yPaint -= gridDim;
	}
	else if (i == 7)
	{
		xPaint += gridDim;
	}
	else
	{
		xPaint -= gridDim;
	}
	colour = getColour(bg[yPaint / gridDim][xPaint / gridDim]);
	drawBlock(gridDim, gridDim, xPaint, yPaint, colour, pixel);
}

void drawGameState(Pixel *pixel,
				   Sprite *mario,
				   Pixel *block,
				   int bg[33][60])
{
	int status = 1;		   // game status
	int numOfButtons = 16; // number of buttons on snes
	int xD = 128;		   // move in x direction
	int yD = 128;		   // move in y direction

	int sX = 32; // for size of the cart
	int sY = 32;

	// press: for knowing which button was pressed
	// i: for tracking the buttons
	// speed: for holding the time delay to simulate speed ups and downs
	int press, i, speed;

	while (status)
	{
		int pressed = 0;
		while (!pressed)
		{
			Read_SNES();
			for (i = 1; i <= numOfButtons; i++)
			{
				if ((i >= 4 || i <= 8) && *(globalButtons + i) == 0)
				{
					// printf("%d was pressed", i);
					pressed = 1;
					press = i;
					break; // break out of the for loop
				}
			}
		}

		// delayMicroseconds(100);
		getCartSpeed(&speed, &xD, &yD, bg); // determine the speed
		determineButtonPressed(press, &xD, &yD, &status, &speed);

		repaint(press, xD, yD, block, bg);
		// delayMicroseconds(speed);
		drawBlock(5, 96, 1536, 704, 0xFF00, block); // draws the finish line
		if (i == 5)
			drawImage(xD, yD, sX, sY, pixel, mario->imgptr_back);
		else if (i == 6)
			drawImage(xD, yD, sX, sY, pixel, mario->imgptr_front);
		else if (i == 7)
			drawImage(xD, yD, sX, sY, pixel, mario->imgptr_left);
		else if (i == 8)
			drawImage(xD, yD, sX, sY, pixel, mario->imgptr_right);

		// drawBlock(32,32, &xD, &yD, 0x0FF0, pixel);
		checkGoal(1536, 704, &xD, &yD, &status);
	}
}

/* Draw a pixel */
void drawPixel(Pixel *pixel)
{
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}

void determineStage()
{
	Sprite *mario;
	mario = malloc(sizeof(Sprite));
	mario->imgptr_right = (short int *)marioImgs.right_data;
	mario->imgptr_left = (short int *)marioImgs.left_data;
	mario->imgptr_front = (short int *)marioImgs.front_data;
	mario->imgptr_back = (short int *)marioImgs.back_data;

	int stage = 1;
	int gameOn = 1;

	/* initialize a pixel */
	Pixel *pixel;
	Pixel *block;

	pixel = malloc(sizeof(Pixel));
	block = malloc(sizeof(Pixel));

	memset(framebufferstruct.fptr, 0, 1);
	while (gameOn)
	{
		if (stage == 1)
		{
			drawNewScene(bg1);
			drawHeader();
			drawGameState(pixel, mario, block, bg1);
			stage++;
		}
		else
		{
			gameOn = 0;
		}
	}
	// drawImage(100, 100, pixel, imagePtr);

	/* free pixel's allocated memory */
	free(pixel);
	free(block);
	pixel = NULL;
	block = NULL;
}

int main()
{
	/* initialize snes contoller*/
	gpioPtr = getGPIOPtr(); // init the virtual base address
	Init_GPIO();			// init the clock, latch, data

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	/* pointers used for cart*/
	determineStage();

	memset(framebufferstruct.fptr, 0, 1);
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

	return 0;
}
