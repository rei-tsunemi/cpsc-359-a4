#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "cart.h"
#include <unistd.h>
#include "initGPIO.h"
#include <time.h>

/*CPSC 359
 * PETER KUCHEL 30008687
 * REI TSUNEMI 30121202
 * 
 * ASSIGNMENT 4
 * 
 * */


#define CLK 11  // clock 
#define LAT 9   // latch 
#define DAT 10  // data 

#define GPSET0 7 	// set registers
#define GPCLR0 10 	// clear registers
#define GPLEV0 13	// level registers


static unsigned int *gpioPtr; // get global gpio pointer
static int globalButtons[16]; // to store the input value from the buttons / register sample buttons

// GPIO setup macros.
#define INP_GPIO(g) *(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3)) // set input
#define OUT_GPIO(g) *(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3))  // set output 

/* Definitions */
typedef struct
{
	short int color;
	int x, y;
} Pixel;

typedef struct
{
	int color;
	int x, y;
} PixelBlock;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);
void drawBackGround(Pixel *pixel);

void Init_GPIO(){
    INP_GPIO(CLK);	
    OUT_GPIO(CLK);      // init clock to output 
    
    INP_GPIO(LAT);	
    OUT_GPIO(LAT); 	// init latch to output
    
    INP_GPIO(DAT);	// init data to input
}

void Write_Latch(int writeData){
    // if writing 1 to the latch pin
    if(writeData == 1){
	gpioPtr[GPSET0] = 1 << LAT;
    }
    
    // else clear the pin
    else{
	gpioPtr[GPCLR0] = 1 << LAT;
    }
}

void Write_Clock(int writeData){
    // if writing 1 to the latch pin
    if(writeData == 1){
	gpioPtr[GPSET0] = 1 << CLK;
    }
    // else clear the pin
    else{
	gpioPtr[GPCLR0] = 1 << CLK;
    }
}


int Read_Data(){
    /*
     * read the data in from the snes controller
     * for the particular button being pressed 
     * 0 means it was pressed 
     * */
    return (gpioPtr[GPLEV0] >> DAT) & 1;
}


void Wait(unsigned int waitTime){
    delayMicroseconds(waitTime); // wait in microseconds 
}


void Read_SNES(){

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
void determineButtonPressed(int i, int *x, int *y, int *status)
{
	int mov = 32;
	if (i == 4)
		*status = 0;
	else if (i == 5){
		(*y)-= mov;
		delayMicroseconds(150000);
	} else if (i == 6){
		(*y)+= mov;
		delayMicroseconds(150000);
	} else if (i == 7){
		(*x)-= mov;
		delayMicroseconds(150000);
	} else if (i == 8){
		(*x)+= mov;
		delayMicroseconds(150000);
	}
}

void repaint(int i, int xD, int yD, PixelBlock *pixel){
	if (i == 5){
		if((yD >= 0) && (yD <= 1056))
			drawBlock(32,32,xD,yD+32,0x00FF, pixel);
	} else if (i == 6){
		if((yD >= 0) && (yD <= 1056))
			drawBlock(32,32,xD,yD-32,0x00FF, pixel);
	} else if (i == 7){
		if((xD >= 0) && (xD <= 1920))
			drawBlock(32,32,xD+32,yD,0x00FF, pixel);
	} else if (i == 8){
		if((xD >= 0) && (xD <= 1920))
			drawBlock(32,32,xD-32,yD,0x00FF, pixel);		
	}
}

void testDraw(Pixel *pixel, short int *imagePtr)
{
	int status = 1;
	int *buttons;
	int numOfButtons = 16;
	int xD = 0;
	int yD = 0;
	int press;
	int initPos = 5;
	int i;

	while (status){
		int pressed = 0;
		while (!pressed){
			Read_SNES();
			for (i = 1; i <= numOfButtons; i++){
				if ((i >= 4 || i <= 8) && *(globalButtons + i) == 0){
					// printf("%d was pressed", i);
					pressed = 1;
					press = i;
					break; // break out of the for loop
				}
			}
		}
		
		
		delayMicroseconds(100);
		determineButtonPressed(press, &xD, &yD, &status);
		repaint(press, xD, yD, pixel);
		drawBlock(5,100,1100,700,0xFF00,pixel);
		drawImage(xD, yD, pixel, imagePtr);
		
		//drawBlock(32,32, &xD, &yD, 0x0FF0, pixel);
		checkGoal(1100, 700, &xD, &yD, &status);
	}
}

void checkGoal(int posX, int posY, int *x, int *y, int *status){
	if(((*x >= posX)&&(*x <= posX+64))&&((*y >= posY)&&(*y <= posY+100))){
		*status = 0;
	} 
}
void fallCliff(int clr, int *x, int *y, int *status){
	if((clr == *x) && (clr == *y)){
		*status = 0;
	}
 
}

void drawImage(int xD, int yD, Pixel *pixel, short int *image){
	int i = 0;
	for (int y = 0; y < 32; y++) {// image height
		for (int x = 0; x < 32; x++) { // image width
			pixel->color = image[i];
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);
			i++;
		}
	}
}

void drawBlock(int sizeX, int sizeY, int xD, int yD, int clr, PixelBlock *pixel){
	int i = 0;
	for (int y = 0; y < sizeY; y++){ // image height
		for (int x = 0; x < sizeX; x++){ // image width
			pixel->color = clr;
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);
			i++;
		}
	}
}

/* Draw a pixel */

void drawBackGround(Pixel *pixel){
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}

void drawPixel(Pixel *pixel){
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}

/* main function */
int main(){
	/* initialize snes contoller*/
	gpioPtr = getGPIOPtr(); 	// init the virtual base address
    Init_GPIO();		// init the clock, latch, data

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	long int screenSize = (long int)framebufferstruct.screenSize;

	// int *imagePtr=(int *) alienImage.image_pixels;
	short int *imagePtr = (short int *)gimp_image.pixel_data;

	/* initialize a pixel */
	Pixel *pixel;
	PixelBlock *block;

	pixel = malloc(sizeof(Pixel));
	block = malloc(sizeof(PixelBlock));

	memset(framebufferstruct.fptr, 0, 1);
	int c = 0;
	int r = 0;
	for(int x=0;x<33; x++){
		c=0;
		for(int y=0; y<60; y++){	
			drawBlock(32,32,c,r,0x00FF,pixel);
			c += 32;
		}
		r += 32;
	}


	testDraw(pixel, imagePtr);	

	/* free pixel's allocated memory */
	free(pixel);
	free(block);
	pixel = NULL;
	block = NULL;

	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

	return 0;
}