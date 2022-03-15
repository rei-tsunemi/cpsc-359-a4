#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#include "framebuffer.h"
#include "alien.h"
#include "home64.h"
#include <wiringPi.h>
#include "initGPIO.h"
/* Definitions */

typedef struct
{
	short int color;
	int x, y;
} Pixel;

typedef struct
{
	int color, x, y;
} BackGround;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

#define CLK 11 // clock
#define LAT 9  // latch
#define DAT 10 // data

#define GPSET0 7  // set registers
#define GPCLR0 10 // clear registers
#define GPLEV0 13 // level registers

static unsigned int *gpioPtr; // get global gpio pointer
static int globalButtons[16]; // to store the input value from the buttons / register sample buttons

// GPIO setup macros.
#define INP_GPIO(g) *(gpioPtr + ((g) / 10)) &= ~(7 << (((g) % 10) * 3)) // set input
#define OUT_GPIO(g) *(gpioPtr + ((g) / 10)) |= (1 << (((g) % 10) * 3))	// set output

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

	// return globalButtons;
}

void drawImage(int xD, int yD, Pixel *pixel, short int *image)
{
	// int yd = yD <= 0 ? 700 + yD : yD;
	int i = 0;
	for (int y = 0; y < 64; y++) // image height
	{
		for (int x = 0; x < 64; x++) // image width
		{
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
	int i = 0;
	for (int y = 0; y < sizeY; y++) // image height
	{
		for (int x = 0; x < sizeX; x++) // image width
		{
			pixel->color = clr;
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);
			i++;
		}
	}
}

/*
	up down left right
	5  6    7    8
*/
void determineButtonPressed(int i, int *x, int *y, int *status)
{
	int d = 10;
	if (i == 4)
		*status = 0;
	else if (i == 5)
		// (*y)--;
		(*y) -= d;
	else if (i == 6)
		// (*y)++;
		(*y) += d;
	else if (i == 7)
		// (*x)--;
		(*x) -= d;
	else if (i == 8)
		// (*x)++;
		(*x) += d;
}
void snesDraw(Pixel *pixel, short int *imagePtr, int xStart, int yStart, long int *screenSize)
{
	int status = 1;
	int numOfButtons = 16;
	int xD = xStart;
	int yD = yStart;
	int press;
	int i;

	while (status)
	{
		int pressed = 0;

		while (!pressed)
		{
			Read_SNES();
			// buttons = globalButtons;
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
		determineButtonPressed(press, &xD, &yD, &status);
		// printf("x is %d, y is %d ", xD, yD);
		if (yD <= 0)
			yD += 750;
		else if (yD >= 1000)
			yD -= 750;

		// memset(framebufferstruct.fptr, 0, *screenSize);
		drawImage(xD, yD, pixel, imagePtr);
		printf("x is %d, y is %d ", xD, yD);
	}
}

/* main function */
int main()
{

	/* initialize gpio + snes*/

	gpioPtr = getGPIOPtr(); // gpio for snes controller
	Init_GPIO();			// init the clock, latch, data
	/*
	up down left right
	5  6    7    8

	*/

	/* initialize + get FBS */

	framebufferstruct = initFbInfo();
	long int screenSize = (long int)framebufferstruct.screenSize;

	// int *imagePtr=(int *) alienImage.image_pixels;
	short int *imagePtr = (short int *)tmpImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	BackGround *backGround;
	pixel = malloc(sizeof(Pixel));
	backGround = malloc(sizeof(BackGround));

	// unsigned int quarter,byte,word;
	memset(framebufferstruct.fptr, 0, screenSize);
	printf("screen size: %ld", screenSize);
	int x = 500;
	int y = 500;
	drawImage(x, y, pixel, imagePtr);
	snesDraw(pixel, imagePtr, x, y, &screenSize);

	/* free pixel's allocated memory */
	// printf("%ld", screenSize);
	free(pixel);
	free(backGround);
	pixel = NULL;
	//~ pixel = malloc(sizeof(Pixel));
	//~ free(pixel);

	/* free up memory*/
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize); // unmap frame ptr
	munmap(gpioPtr, 4096);										  // unmap gpio pointer
	// free(buttons);

	return 0;
}

/* Draw a pixel */

void drawPixel(Pixel *pixel)
{
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}
