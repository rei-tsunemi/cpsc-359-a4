#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>
#include <pthread.h>

#include "framebuffer.h"
#include "initGPIO.h"
#include "initGame.h"

//#include "backgrounds.h"
//#include "sprites.h"

#include "title.h"
#include "titleStart.h"
#include "titlequit.h"


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

// static int gridSize = 32;
// static int baseSpeed = 55000;
static unsigned int *gpioPtr; // get global gpio pointer
static int globalButtons[16]; // to store the input value from the buttons / register sample buttons
GameState *gamestate;		  // global gamestate

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

void getCartSpeed(int *speed, int *x, int *y, int bg[Y_DIM][X_DIM])
{
	int colourPos = bg[*y / gridSize][*x / gridSize];
	if (colourPos != 2)
		*speed = baseSpeed * 4;
	// *speed = baseSpeed;
	else

		*speed = baseSpeed;
}

void determineButtonPressed(int i, int *x, int *y, int *status, int *speed)
{
	// int mov = 32;
	if (i == 4)
		*status = 0;
	else if (i == 5)
	{
		if ((*y) == 64)
			(*y) = (*y);
		else
			(*y) -= gridSize;
	}
	else if (i == 6)
	{
		if ((*y) == 1024)
			(*y) = (*y);
		else
			(*y) += gridSize;
	}
	else if (i == 7)
	{
		if ((*x) == 0)
			(*x) = (*x);
		else
			(*x) -= gridSize;
	}
	else if (i == 8)
	{
		if ((*x) == 1888)
			(*x) = (*x);
		else
			(*x) += gridSize;
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

void drawHeader(Alphabet *word){
	int dim = 64; //dimention of each alphabet
	Pixel *pix;
	pix = malloc(sizeof(Pixel));


	/* printing all alphabet for level */
	drawImage(0, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(64, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(128, 0, dim, dim, pix, word->alpPtr_v);
	drawImage(192, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(256, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(320, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for life */
	drawImage(448, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(512, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(576, 0, dim, dim, pix, word->alpPtr_f);
	drawImage(640, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(704, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for score */
	drawImage(832, 0, dim, dim, pix, word->alpPtr_s);
	drawImage(896, 0, dim, dim, pix, word->alpPtr_c);
	drawImage(960, 0, dim, dim, pix, word->alpPtr_o);
	drawImage(1024, 0, dim, dim, pix, word->alpPtr_r);
	drawImage(1088, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1152, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for time */
	drawImage(1408, 0, dim, dim, pix, word->alpPtr_t);
	drawImage(1472, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(1536, 0, dim, dim, pix, word->alpPtr_m);
	drawImage(1600, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1664, 0, dim, dim, pix, word->alpPtr_colon);

	free(pix);
}

void drawNewScene(int bg[Y_DIM][X_DIM])
{
	// int blockSize = 32;
	int xSize = 60;
	int ySize = 33;
	Pixel *scenePixel = malloc(sizeof(Pixel));
	int yOff, xOff;
	for (int y = 0; y < ySize; y++)
	{
		yOff = y * gridSize;
		for (int x = 0; x < xSize; x++)
		{
			xOff = x * gridSize;
			int colour = getColour(bg[y][x]);
			drawBlock(gridSize, gridSize, xOff, yOff, colour, scenePixel);
		}
	}
	free(scenePixel);
}

void repaint(int i, int xD, int yD, Pixel *pixel, int bg[Y_DIM][X_DIM])
{
	// int gridDim = 32;
	int xPaint = xD;
	int yPaint = yD;
	int colour;

	if (i == 5)
	{
		yPaint += gridSize;
	}
	else if (i == 6)
	{
		yPaint -= gridSize;
	}
	else if (i == 7)
	{
		xPaint += gridSize;
	}
	else
	{
		xPaint -= gridSize;
	}
	colour = getColour(bg[yPaint / gridSize][xPaint / gridSize]);
	drawBlock(gridSize, gridSize, xPaint, yPaint, colour, pixel);
}

void drawMovingSprite(Pixel *pixel, Sprite *sprite, Pixel *block, int bg[Y_DIM][X_DIM])
{
}

void drawGameState(Pixel *pixel,
				   Sprite *currentSprite,
				   Pixel *block,
				   int bg[Y_DIM][X_DIM])
{
	int status = 1;		   // game status
	int numOfButtons = 16; // number of buttons on snes
	int xD = 192;		   // move in x direction
	int yD = 128;		   // move in y direction

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

		getCartSpeed(&speed, &xD, &yD, bg); // determine the speed
		determineButtonPressed(press, &xD, &yD, &status, &speed);

		repaint(press, xD, yD, block, bg);

		if (i == 5)
			drawImage(xD, yD, currentSprite->drawSize, currentSprite->drawSize, pixel, currentSprite->imgptr_back);
		else if (i == 6)
			drawImage(xD, yD, currentSprite->drawSize, currentSprite->drawSize, pixel, currentSprite->imgptr_front);
		else if (i == 7)
			drawImage(xD, yD, currentSprite->drawSize, currentSprite->drawSize, pixel, currentSprite->imgptr_left);
		else if (i == 8)
			drawImage(xD, yD, currentSprite->drawSize, currentSprite->drawSize, pixel, currentSprite->imgptr_right);

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

void screenMenu(int *game, int *stg){
	Pixel *pix;
	pix = malloc(sizeof(Pixel));
	short int *menuPtr = (short int *)img_title.pixel_data;
	short int *startPtr = (short int *)img_start.pixel_data;
	short int *quitPtr = (short int *)img_quit.pixel_data;

	int numOfButtons = 16; // number of buttons on snes
	int i;
	int status = 1;
	int start = 0;
	int quit = 0;

	drawImage(0, 0, 1024, 1920 ,pix, menuPtr);

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
					break; // break out of the for loop
				}
			}
		}
		if (i == 5){
			drawImage(0, 0, 1024, 1920 ,pix, startPtr);
			start = 1;
			quit = 0;
		} else if (i == 6) {
			drawImage(0, 0, 1024, 1920 ,pix, quitPtr);
			quit = 1;
			start = 0;
		} else if (i == 9){
			if(start == 1) {
				(*stg) = 1;
				status = 0;
			} else if(quit == 1){
				drawBlock(1920, 1024, 0, 0, 0x0000, pix);
				(*game) = 0;
				status = 0;
			}
		}
	}
}


void determineStage()
{
	Sprite *mario;
	Alphabet *alp;
	Numeric *num;
	// Sprite *spike;

	gamestate = malloc(sizeof(GameState));
	initScene1(gamestate);
	mario = malloc(sizeof(Sprite));
	alp = malloc(sizeof(Alphabet));
	num = malloc(sizeof(Numeric));
	initMario(mario);
	initAlphabet(alp);
	initNumeric(num);

	// spike = malloc(sizeof(Sprite));

	int stage = 0;
	int gameOn = 1;

	/* initialize a pixel */
	Pixel *pixel;
	Pixel *block;

	pixel = malloc(sizeof(Pixel));
	block = malloc(sizeof(Pixel));
	memset(framebufferstruct.fptr, 0, 1);

	while (gameOn)
	{
		if (stage == 0){
			screenMenu(&gameOn, &stage);
		}
		else if (stage == 1)
		{
			// drawNewScene(bg1);
			drawNewScene((*gamestate).bg);
			drawHeader(alp);
			drawBlock(5, 96, 1536, 704, 0xFF00, block); // draws the finish line
			drawImage(mario->xStart, mario->yStart, gridSize, gridSize, pixel, mario->imgptr_front);
			// drawGameState(pixel, mario, block, bg1);
			drawGameState(pixel, mario, block, (*gamestate).bg);

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
	free(mario);
	free(alp);
	free(num);
	free(gamestate);
	// free(spike);
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
