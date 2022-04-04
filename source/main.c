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

#include "pauseMenu.h"
#include "pauseRestart.h"
#include "pauseQuit.h"

/*CPSC 359
 * PETER KUCHEL 30008687
 * REI TSUNEMI 30121202
 *
 * ASSIGNMENT 4
 *
 *
 * art for mario from: https://www.spriters-resource.com/custom_edited/mariocustoms/sheet/62611/
 * art for the bugs from:
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

DigitsToDraw *digitsToDraw; // global struct pointer to draw digits at their correct positions
// BackGroundImages *backGrounds;
Screens *screens;

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
void drawPauseMenu(GameState *gamestate, int *x, int *y, Mario *m, int *status, Pixel *pix);
void determineStage();

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

/* Draw a pixel */

void drawPixel(Pixel *pixel)
{
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}

int getColour(int num)
{
	if (num == 0)
		return 0xFFFF; // white
	else if (num == 1)
		return 0x0000; // black
	else if (num == 2)
		return 0x8430; // grey
	else if (num == 3)
		return 0xC841; // red
	else if (num == 4)
		return 0x00FF; // blue
	else if (num == 5)
		return 0x24c4; // light green
	else if (num == 6)
		return 0xCEE2; // creamy yellow
	else if (num == 7)
		return 0x0000; // black
	else
		return 0x0000; // black
}

void assignBackGround(short int *tile, short int *image)
{
	int i;
	for (i = 0; i < backgroundSize; i++)
		*(tile + i) = *(image + i);
}

// void getBackGroundImage(short int *bgTile, int bgPos)
// {
// 	int i;
// 	if (bgPos == 0)
// 	{
// 		for (i = 0; i < backgroundSize; i++)
// 			*(bgTile + i) = 0xFFFF;
// 	}
// 	else if (bgPos == 1 || bgPos == 7)
// 	{
// 		for (i = 0; i < backgroundSize; i++)
// 			*(bgTile + i) = 0x0000;
// 	}
// 	else if (bgPos == 2)
// 	{
// 		assignBackGround(bgTile, backGrounds->road);
// 	}
// 	else if (bgPos == 3)
// 	{
// 		assignBackGround(bgTile, backGrounds->lava);
// 	}
// 	else if (bgPos == 4)
// 	{
// 		assignBackGround(bgTile, backGrounds->water);
// 	}
// 	else if (bgPos == 5)
// 	{
// 		assignBackGround(bgTile, backGrounds->grass1);
// 	}
// 	else if (bgPos == 6)
// 	{
// 		assignBackGround(bgTile, backGrounds->rainbow);
// 	}
// 	// else if (bgPos == 7)
// 	// {
// 	// 	assignBackGround(bgTile, backGrounds->water);
// 	// }
// }

int getBackGroundColour(GameState *gs, int *x, int *y)
{
	int colour;
	colour = gs->bg[*y / gridSize][*x / gridSize];
	return getColour(colour);
}

void checkCollision(int *x, int *y, int *xToCheck, int *yToCheck, int *flag)
{
	if ((*x == *xToCheck) && (*y == *yToCheck))
	{
		*flag = 1;
	}
}

void getCartSpeed(int *speed, int *x, int *y, int bg[Y_DIM][X_DIM], int *speedBonus)
{

	// *speed = baseSpeed;
	int colourPos = bg[*y / gridSize][*x / gridSize];

	if (*speedBonus)
	{
		return;
	}
	else if (colourPos == 2 || colourPos == 6)
	{
		*speed = baseSpeed;
	}
	else
	{
		*speed = baseSpeed * 4;
		*speedBonus = 0;
	}
}

void determineButtonPressed(int i, int *x, int *y, GameState *gs)
{
	int j;
	int treeCollision = 0;
	int numOfTrees = gs->spritesForScene->trees;
	int xPrev = *x;
	int yPrev = *y;

	// int mov = 32;
	if (i == 5)
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
	for (j = 0; j < numOfTrees; j++)
	{
		checkCollision(x, y,
					   &((gs->treeSpots + j)->xStart),
					   &((gs->treeSpots + j)->yStart),
					   &treeCollision);
		if (treeCollision)
		{
			*x = xPrev;
			*y = yPrev;
			return;
		}
	}
}

void drawImage(int xD, int yD, int sizeX, int sizeY, Pixel *pixel, short int *image)
{
	int i = 0;
	for (int y = 0; y < sizeX; y++) // image height
	{
		for (int x = 0; x < sizeY; x++) // image width
		{
			pixel->color = image[i];
			pixel->x = x + xD;
			pixel->y = y + yD;

			drawPixel(pixel);

			i++;
		}
	}
}

void drawSprite(int xD, int yD, int sizeX, int sizeY, Pixel *pixel, short int *image, unsigned int nocolor)
{
	int i = 0;
	for (int y = 0; y < sizeX; y++) // image height
	{
		for (int x = 0; x < sizeY; x++) // image width
		{
			pixel->color = image[i];
			pixel->x = x + xD;
			pixel->y = y + yD;
			if (image[i] != nocolor)
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

void drawHeader(Alphabet *word, Pixel *pix)
{
	int dim = 64; // dimention of each alphabet

	/* printing all alphabet for level */
	drawImage(0, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(64, 0, dim, dim, pix, word->alpPtr_v);
	drawImage(128, 0, dim, dim, pix, word->alpPtr_l);

	/* printing all alphabet for life */
	drawImage(320, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(384, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(448, 0, dim, dim, pix, word->alpPtr_f);
	drawImage(512, 0, dim, dim, pix, word->alpPtr_e);

	/* printing all alphabet for score */
	drawImage(704, 0, dim, dim, pix, word->alpPtr_s);
	drawImage(768, 0, dim, dim, pix, word->alpPtr_c);
	drawImage(832, 0, dim, dim, pix, word->alpPtr_o);
	drawImage(896, 0, dim, dim, pix, word->alpPtr_r);
	drawImage(960, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1024, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for time */
	drawImage(1408, 0, dim, dim, pix, word->alpPtr_t);
	drawImage(1472, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(1536, 0, dim, dim, pix, word->alpPtr_m);
	drawImage(1600, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1664, 0, dim, dim, pix, word->alpPtr_colon);
}

void clearScreen(Pixel *pixel)
{
	int xD = 1920;
	int yD = 1080;
	int colour = 0x0000;
	drawBlock(xD, yD, 0, 0, colour, pixel);
}

void repaint(int i, int xD, int yD, Pixel *pixel, int bg[Y_DIM][X_DIM])
{
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
	// colour = bg[yPaint / gridSize][xPaint / gridSize];
	// getBackGroundImage(tile, colour);
	// drawImage(xPaint, yPaint, gridSize, gridSize, pixel, tile);

	colour = getColour(bg[yPaint / gridSize][xPaint / gridSize]);
	drawBlock(gridSize, gridSize, xPaint, yPaint, colour, pixel);
}

void findBugCurrentSpot(int *xD, int *yD, int *xP, int *yP, BugPositions *bugSpot)
{
	int offSet = gridSize;
	int currentShift = bugSpot->posShift;
	int moveD = bugSpot->moveDirection;

	*xP = bugSpot->xStart;
	*yP = bugSpot->yStart;

	*xD = bugSpot->xStart;
	*yD = bugSpot->yStart;

	if (bugSpot->moveVector == 1)
	{
		*xD += (offSet * (currentShift + 1) * moveD);
		*xP += (offSet * currentShift * moveD);
	}
	else
	{
		*yD += (offSet * (currentShift + 1) * moveD);
		*yP += (offSet * currentShift * moveD);
	}
}

void bugCollision(int *xD, int *yD, GameState *gs)
{

	if (gs->mario->canGetHit)
	{
		if ((*xD == gs->mario->xPos) && (*yD == gs->mario->yPos))
			gs->mario->gotHit = 1;

		if ((*xD == gs->mario->xPrev) && (*yD == gs->mario->yPrev))
			gs->mario->gotHit = 1;
	}
}

void drawBugs(Pixel *pixel, GameState *gs, short int *tile)
{

	int i, colour, currentShift, moveD;
	int xD, yD, xPrev, yPrev;
	int bugsToPrint = gs->spritesForScene->bugs;
	BugSprite *bug = gs->bugs;

	for (i = 0; i < bugsToPrint; i++)
	{

		currentShift = (gs->bugSpots + i)->posShift;
		moveD = (gs->bugSpots + i)->moveDirection;
		bugCollision(&xD, &yD, gs);

		findBugCurrentSpot(&xD, &yD, &xPrev, &yPrev, (gs->bugSpots + i));

		currentShift++;

		colour = getColour(gs->bg[yPrev / gridSize][xPrev / gridSize]);
		// colour = gs->bg[yPrev / gridSize][xPrev / gridSize];
		// getColour()
		// getBackGroundImage(tile, colour);
		// drawImage(xPrev, yPrev, gridSize, gridSize, pixel, tile);

		drawBlock(gridSize, gridSize, xPrev, yPrev, colour, pixel);
		bugCollision(&xD, &yD, gs);

		if (moveD == 1)
			drawSprite(xD, yD, bug->drawSize, bug->drawSize, pixel, bug->imgptr_right, -1);
		else
			drawSprite(xD, yD, bug->drawSize, bug->drawSize, pixel, bug->imgptr_left, -1);

		if ((currentShift + 1) == (gs->bugSpots + i)->maxPosShift)
		{
			currentShift = 0;
			moveD *= -1;
			(gs->bugSpots + i)->xStart = xD;
			(gs->bugSpots + i)->yStart = yD;
		}

		(gs->bugSpots + i)->posShift = currentShift;
		(gs->bugSpots + i)->moveDirection = moveD;
	}
	delayMicroseconds(35000);
}

void *drawBugsAtPos(void *param)
{
	GameState *gamestate = (GameState *)param;
	Pixel *pixel = malloc(sizeof(Pixel));
	short int *tile = malloc(sizeof(short int *) * backgroundSize);
	if (pixel == NULL || tile == NULL)
	{
		printf("failed to allocate in function drawBugsAPos, exiting now\n");
		gamestate->sceneStatus = 0;
		gamestate->gameOn = 0;
		pthread_exit(0);
	}

	while (gamestate->sceneStatus)
	{
		drawBugs(pixel, gamestate, tile);
	}
	free(tile);
	free(pixel);
	tile = NULL;
	pixel = NULL;

	pthread_exit(0);
}

void drawValuePack(Pixel *pixel, GameState *gs)
{
	ItemBlock *itm = gs->itemblocks;
	int numOfItems = gs->spritesForScene->items;
	int i, drawFace, xD, yD, visible;
	int bgColour;
	for (i = 0; i < numOfItems; i++)
	{

		visible = (gs->itemSpots + i)->isVisible;
		if (visible)
		{
			xD = (gs->itemSpots + i)->xStart;
			yD = (gs->itemSpots + i)->yStart;
			drawFace = (gs->itemSpots + i)->drawFace;
			bgColour = getBackGroundColour(gs, &xD, &yD);
			// bgColour = gs->bg[yD / gridSize][xD / gridSize];
			// getBackGroundImage(tile, bgColour);
			// drawImage(xD, yD, gridSize, gridSize, pixel, tile);
			drawBlock(itm->drawSize, itm->drawSize, xD, yD, bgColour, pixel);

			if (drawFace == 0)
				drawSprite(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_F, -16391);

			else if (drawFace == 1)
				drawSprite(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_s1, -16391);

			else if (drawFace == 2)
				drawSprite(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_s2, -16391);

			drawFace++;
			if (drawFace == 3)
				drawFace = 0;

			(gs->itemSpots + i)->drawFace = drawFace;
		}
	}
	Wait(200000);
}

void drawCoins(Pixel *pixel, GameState *gs)
{
	Coin *cn = gs->coins;
	int numOfCoins = gs->spritesForScene->coins;
	int i, drawFace, xD, yD, visible;
	int bgColour;
	for (i = 0; i < numOfCoins; i++)
	{
		visible = (gs->coinSpots + i)->isVisible;
		if (visible)
		{
			xD = (gs->coinSpots + i)->xStart;
			yD = (gs->coinSpots + i)->yStart;
			drawFace = (gs->coinSpots + i)->drawFace;
			// bgColour = gs->bg[yD / gridSize][xD / gridSize];
			// getBackGroundImage(tile, bgColour);
			// drawImage(xD, yD, gridSize, gridSize, pixel, tile);

			bgColour = getBackGroundColour(gs, &xD, &yD);
			drawBlock(cn->drawSize, cn->drawSize, xD, yD, bgColour, pixel);

			if (drawFace == 0)
				drawSprite(xD, yD, cn->drawSize, cn->drawSize, pixel, cn->coinPtr_side, 1215);

			else if (drawFace == 1)
				drawSprite(xD, yD, cn->drawSize, cn->drawSize, pixel, cn->coinPtr_left, 1215);

			else if (drawFace == 2)
				drawSprite(xD, yD, cn->drawSize, cn->drawSize, pixel, cn->coinPtr_front, 1215);

			else if (drawFace == 3)
				drawSprite(xD, yD, cn->drawSize, cn->drawSize, pixel, cn->coinPtr_right, 1215);

			drawFace++;
			if (drawFace == 4)
				drawFace = 0;
			(gs->coinSpots + i)->drawFace = drawFace;
		}
	}
	Wait(100000);
}

void *animateValuePack(void *param)
{
	GameState *gamestate = (GameState *)param;
	Pixel *pix = malloc(sizeof(Pixel));
	if (pix == NULL)
	{
		printf("in function animateValuePack memory  alloc failed,exiting now\n");
		gamestate->sceneStatus = 0;
		gamestate->gameOn = 0;
		pthread_exit(0);
	}

	while (gamestate->sceneStatus)
	{
		drawValuePack(pix, gamestate);
		drawCoins(pix, gamestate);
	}
	free(pix);
	pix = NULL;

	pthread_exit(0);
}

void drawTime(GameState *gamestate, Pixel *pixel)
{

	int check = 10;
	int hundred = (gamestate->timeLeft / 100) % check;
	int ten = (gamestate->timeLeft / 10) % check;
	int one = (gamestate->timeLeft / 1) % check;

	int size = digitsToDraw->timeDraw->gridSize;
	int xPos = digitsToDraw->timeDraw->xPos;
	int yPos = digitsToDraw->timeDraw->yPos;

	int i;
	for (i = 0; i < 10; i++)
	{
		if (hundred == i)
			drawImage(xPos, yPos, size, size, pixel, *(digitsToDraw->digits + i));

		if (ten == i)
			drawImage(xPos + size, yPos, size, size, pixel, *(digitsToDraw->digits + i));

		if (one == i)
			drawImage(xPos + (2 * size), yPos, size, size, pixel, *(digitsToDraw->digits + i));
	}
}

void *timerThread(void *param)
{
	GameState *gamestate = (GameState *)param;
	Pixel *pix = malloc(sizeof(Pixel));
	if (pix == NULL)
	{
		printf("could not allocate memory in function timerThread, exiting now\n");
		gamestate->sceneStatus = 0;
		gamestate->gameOn = 0;
		pthread_exit(0);
	}

	while (gamestate->timeLeft != -1 && gamestate->sceneStatus)
	{
		drawTime(gamestate, pix);
		sleep(1);
		gamestate->timeLeft -= 1;
	}
	free(pix);
	pix = NULL;
	pthread_exit(0);
}

void drawLivesDisplay(GameState *gamestate, Pixel *pixel)
{

	drawImage(digitsToDraw->livesDraw->xPos,
			  digitsToDraw->livesDraw->yPos,
			  digitsToDraw->livesDraw->gridSize,
			  digitsToDraw->livesDraw->gridSize,
			  pixel,
			  *(digitsToDraw->digits + gamestate->lives));
}

void drawScoreDisplay(GameState *gamestate, Pixel *pixel)
{
	int currentScore = gamestate->score;
	int check = 10;
	int thousand = (currentScore / 1000) % check;
	int hundred = (currentScore / 100) % check;
	int ten = (currentScore / 10) % check;
	int one = (currentScore / 1) % check;

	int size = digitsToDraw->scoreDraw->gridSize;
	int xPos = digitsToDraw->scoreDraw->xPos;
	int yPos = digitsToDraw->scoreDraw->yPos;

	int i;
	for (i = 0; i < 10; i++)
	{
		if (thousand == i)
			drawImage(xPos, yPos, size, size, pixel, *(digitsToDraw->digits + i));
		if (hundred == i)
			drawImage(xPos + size, yPos, size, size, pixel, *(digitsToDraw->digits + i));
		if (ten == i)
			drawImage(xPos + (2 * size), yPos, size, size, pixel, *(digitsToDraw->digits + i));
		if (one == i)
			drawImage(xPos + (3 * size), yPos, size, size, pixel, *(digitsToDraw->digits + i));
	}
}

void drawLevelDisplay(int scene, Pixel *pixel)
{
	int grdsz = digitsToDraw->lvlDraw->gridSize;
	int x = digitsToDraw->lvlDraw->xPos;
	int y = digitsToDraw->lvlDraw->yPos;
	drawImage(x, y, grdsz, grdsz, pixel, *(digitsToDraw->digits + scene));
}

void calcScenceEndScore(GameState *gs, Pixel *pixel)
{
	float scoreMultiplier = 1.1;
	float timeBonus = 100;
	float time = (float)gs->timeLeft;
	float lives = (float)gs->lives;
	float currentScore = (float)gs->score;
	currentScore += (time + (lives * timeBonus)) * scoreMultiplier;
	gs->score = (int)currentScore;
	drawScoreDisplay(gs, pixel);
}

void didMarioCollideWithAnything(int *xD, int *yD, GameState *gs)
{
	// bug x and y positions ( move and previous )
	int bX, bY, bxP, byP;
	int j;
	int numOfBugs = gs->spritesForScene->bugs;
	// test first if mario collided with bugs
	for (j = 0; j < numOfBugs; j++)
	{
		findBugCurrentSpot(&bX, &bY, &bxP, &byP, (gs->bugSpots + j));

		if (gs->mario->canGetHit)
		{
			checkCollision(xD, yD, &bX, &bY, &(gs->mario->gotHit));
			checkCollision(xD, yD, &bxP, &byP, &(gs->mario->gotHit));
		}
		if (gs->mario->gotHit == 1)
		{
			// printf("mario got hit ");
			return;
		}
	}
	int numOfPacks = gs->spritesForScene->items;
	int visible;
	for (j = 0; j < numOfPacks; j++)
	{
		visible = (gs->itemSpots + j)->isVisible;

		if (visible)
		{
			bX = (gs->itemSpots + j)->xStart;
			bY = (gs->itemSpots + j)->yStart;
			checkCollision(xD, yD, &bX, &bY, &(gs->mario->didHitPack));
		}

		if (gs->mario->didHitPack)
		{
			gs->mario->packCollidedWith = j;
			return;
		}
	}
	int numOfCoins = gs->spritesForScene->coins;
	for (j = 0; j < numOfCoins; j++)
	{
		visible = (gs->coinSpots + j)->isVisible;
		if (visible)
		{
			bX = (gs->coinSpots + j)->xStart;
			bY = (gs->coinSpots + j)->yStart;
			checkCollision(xD, yD, &bX, &bY, &(gs->mario->didGetCoin));
		}
		if (gs->mario->didGetCoin)
		{
			gs->mario->coinGotten = j;
			return;
		}
	}
}

void determineValuePackEffect(Mario *mario, GameState *gs, Pixel *pixel)
{

	int packChoices = 5;
	int rng = rand() % packChoices;
	// int rng = 0;
	if (rng == 0)
	{
		gs->score += 15;
		drawScoreDisplay(gs, pixel);
	}
	else if (rng == 1)
	{
		int current = gs->lives;
		if (current + 3 <= 9)
			current += 3;
		else
			current = 9;

		gs->lives = current;
		drawLivesDisplay(gs, pixel);
	}
	else if (rng == 2)
	{
		gs->timeLeft += 45;
	}
	else if (rng == 3)
	{
		mario->moveSpeed += 200000;
		// mario->moveSpeed += 1;
		mario->speedBonus = 1;
	}
	else if (rng == 4)
	{
		mario->moveSpeed -= 25000;
		if (mario->moveSpeed <= 0)
			mario->moveSpeed = 100;
		mario->speedBonus = 1;
	}
}

void backGroundDeathZones(int *pos, int *flag)
{
	// these numbers correspond to the colour map positions
	if (*pos == 4 || *pos == 3 || *pos == 7)
		*flag = 1;
	else
		*flag = 0;
}

void testForCollisions(Mario *mario,
					   int *xD,
					   int *yD,
					   Pixel *pixel,
					   GameState *gs,
					   int *status,
					   int *press)
{
	int marioFell = 0;

	int colour = getColour(gs->bg[*yD / gridSize][*xD / gridSize]);

	// int backGroundPos = gs->bg[*yD / gridSize][*xD / gridSize];
	// backGroundDeathZones(&backGroundPos, &marioFell);

	if (gs->mario->gotHit == 1 || marioFell)
	{

		gs->mario->canGetHit = 0;
		int l = gs->lives;
		l--;
		gs->lives = l;

		int i;
		int fallSpin = 0;
		for (i = 0; i < 10; i++)
		{
			if (fallSpin == 0)
				drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front, -31505);

			else if (fallSpin == 1)
				drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_left, -31505);
			else if (fallSpin == 2)
				drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_back, -31505);
			else
				drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_right, -31505);
			delayMicroseconds(150000);

			drawBlock(mario->drawSize, mario->drawSize, *xD, *yD, colour, pixel);
			// drawImage(*xD, *yD, gridSize, gridSize, pixel, bgTile);
			if (fallSpin == 3)
				fallSpin = 0;
			else
				fallSpin++;
		}
		drawBlock(mario->drawSize, mario->drawSize, *xD, *yD, colour, pixel);
		// drawImage(*xD, *yD, gridSize, gridSize, pixel, bgTile);

		*xD = mario->xStart;
		*yD = mario->yStart;
		gs->mario->xPos = *xD;
		gs->mario->yPos = *yD;
		gs->mario->xPrev = *xD;
		gs->mario->yPrev = *yD;

		drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front, -31505);

		gs->mario->moveSpeed = baseSpeed;
		gs->mario->speedBonus = 0;
		gs->mario->gotHit = 0;
		gs->mario->canGetHit = 1;

		if (gs->lives >= 0)
			drawLivesDisplay(gs, pixel);
	}
	else if (mario->didHitPack)
	{

		int packPos = mario->packCollidedWith;
		// int colour = getColour(gs->bg[*yD / gridSize][*xD / gridSize]);

		int drawSize = gs->itemblocks->drawSize;
		drawBlock(drawSize, drawSize, *xD, *yD, colour, pixel);
		drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front, -31505);

		determineValuePackEffect(mario, gs, pixel);

		(gs->itemSpots + packPos)->isVisible = 0;
		mario->didHitPack = 0;
		mario->packCollidedWith = -1;
	}
	else if (mario->didGetCoin)
	{
		int coinGot = mario->coinGotten;
		// int colour = getColour(gs->bg[*yD / gridSize][*xD / gridSize]);
		int drawSize = gs->coins->drawSize;

		drawBlock(drawSize, drawSize, *xD, *yD, colour, pixel);
		drawSprite(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front, -31505);

		if (gs->scene == 1)
			gs->score += 5;

		else if (gs->scene == 2)
			gs->score += 10;

		else if (gs->scene == 3)
			gs->score += 15;

		else if (gs->scene == 4)
			gs->score += 20;

		drawScoreDisplay(gs, pixel);

		(gs->coinSpots + coinGot)->isVisible = 0;
		mario->didGetCoin = 0;
		mario->coinGotten = -1;
	}
	else // check goal
	{
		if ((*xD >= gs->goal->xPos) &&
			(*xD <= (gs->goal->xPos + gs->goal->xSize)) &&
			(*yD >= gs->goal->yPos) &&
			(*yD <= (gs->goal->yPos + gs->goal->ySize)))

		{
			*status = 0;
			gs->winCond = 1;
			gs->sceneStatus = 0;
			Wait(100000);
		}
	}
}
void drawPauseMenu(GameState *gamestate, int *x, int *y, Mario *m, int *status, Pixel *pix)
{
	int paused = 1;
	int numOfButtons = 16; // number of buttons on snes
	int i;
	int restart = 0;
	int quit = 0;
	int xStart = 420;
	int yStart = 250;

	short int *pausemenuPtr = (short int *)pause_M.pixel_data;
	short int *restartPtr = (short int *)pause_R.pixel_data;
	short int *quitgamePtr = (short int *)pause_Q.pixel_data;

	drawImage(xStart, yStart, 576, 1056, pix, pausemenuPtr);
	while (paused)
	{
		int pressed = 0;
		while (!pressed)
		{
			Read_SNES();
			for (i = 1; i <= numOfButtons; i++)
			{
				if ((i >= 4 || i <= 8) && *(globalButtons + i) == 0)
				{
					pressed = 1;
					break; // break out of the for loop
				}
			}
		}
		if (i == 4)
		{
			(*x) = m->xPos;
			(*y) = m->yPos;
			paused = 0;
			*status = 1;
			gamestate->sceneStatus = 2;
			Wait(800000);
		}
		else if (i == 5)
		{
			drawImage(xStart, yStart, 576, 1056, pix, restartPtr);
			quit = 0;
			restart = 1;
		}
		else if (i == 6)
		{
			drawImage(xStart, yStart, 576, 1056, pix, quitgamePtr);
			quit = 1;
			restart = 0;
		}
		else if (i == 9)
		{
			if (restart == 1)
			{
				gamestate->scene = 1;
				gamestate->sceneStatus = 0;
				gamestate->winCond = 0;
				gamestate->score = 0;
				paused = 0;
			}
			else if (quit == 1)
			{
				paused = 0;
				gamestate->scene = 0;
				gamestate->sceneStatus = 0;
				gamestate->winCond = 0;
			}
		}
	}
}

void checkForLoseCond(GameState *gs, int *flag)
{
	if (gs->lives <= 0)
	{
		gs->loseCond = 1;
		*flag = 0;
	}
	else if (gs->timeLeft == -1)
	{
		gs->loseCond = 2;
		*flag = 0;
	}
}

void drawGameState(Pixel *pixel,
				   GameState *gamestate,
				   int bg[Y_DIM][X_DIM])
{
	Mario *mario = gamestate->mario;
	int status = 1;		   // game status
	int numOfButtons = 16; // number of buttons on snes
	int xD = mario->xPos;  // move in x direction
	int yD = mario->yPos;  // move in y direction

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t bugThread, timeT, itemThread;

	pthread_create(&bugThread, &attr, drawBugsAtPos, gamestate);
	pthread_create(&itemThread, &attr, animateValuePack, gamestate);
	pthread_create(&timeT, &attr, timerThread, gamestate);

	// press: for knowing which button was pressed
	// i: for tracking the buttons
	// speed: for holding the time delay to simulate speed ups and downs
	int press, i;
	// int speed;
	// speed = baseSpeed * 4;
	// speed = baseSpeed;
	while (status && (gamestate->sceneStatus == 1))
	{
		int pressed = 0;

		while (!pressed)
		{
			Read_SNES();
			for (i = 1; i <= numOfButtons; i++)
			{

				// test if anything collided while reading input
				didMarioCollideWithAnything(&xD, &yD, gamestate);
				testForCollisions(mario, &xD, &yD, pixel, gamestate, &status, &press);
				checkForLoseCond(gamestate, &status);

				if ((i >= 4 || i <= 8) && *(globalButtons + i) == 0)
				{
					pressed = 1;
					press = i;
					break; // break out of the for loop
				}
				if (!status)
				{
					pressed = 1;
					break;
				}
				// set previous position to stationary position if no longer reading input from snes
				mario->xPrev = xD;
				mario->yPrev = yD;
			}
		}
		if (!status)
		{
			// printf("lose cond\n");
			break;
		}

		mario->xPrev = xD;
		mario->yPrev = yD;

		getCartSpeed(&(mario->moveSpeed), &xD, &yD, gamestate->bg, &(mario->speedBonus));
		determineButtonPressed(press, &xD, &yD, gamestate);

		mario->xPos = xD;
		mario->yPos = yD;

		didMarioCollideWithAnything(&xD, &yD, gamestate);
		delayMicroseconds(mario->moveSpeed); // delay to make it seem likes the cart moves slower

		repaint(press, xD, yD, pixel, gamestate->bg);
		testForCollisions(mario, &xD, &yD, pixel, gamestate, &status, &press);

		if (i == 4)
		{
			gamestate->sceneStatus = 0;
			Wait(800000);
			drawPauseMenu(gamestate, &xD, &yD, mario, &status, pixel);
		}
		else if (press == 5)
			drawSprite(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_back, -31505);
		else if (press == 6)
			drawSprite(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front, -31505);
		else if (press == 7)
			drawSprite(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_left, -31505);
		else if (press == 8)
			drawSprite(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_right, -31505);
	}
	if (status == 0)
	{
		gamestate->sceneStatus = 0;
	}

	pthread_join(bugThread, NULL);
	pthread_join(timeT, NULL);
	pthread_join(itemThread, NULL);
}

void pressAnyButton()
{
	int i, pressed;
	int numOfButtons = 16;
	pressed = 0;

	while (!pressed)
	{
		Read_SNES();
		for (i = 1; i <= numOfButtons; i++)
		{

			if (*(globalButtons + i) == 0)
			{
				pressed = 1;
				break; // break out of the for loop
			}
		}
	}
}
void drawWinLose(GameState *gs, Alphabet *alp, Pixel *pixel)
{
	if (gs->scene == 5)
	{
		drawImage(0, 64, 1016, 1920, pixel, screens->winScreen);
		drawHeader(alp, pixel);
		sleep(2);
		pressAnyButton();
	}
	else
	{
		drawImage(0, 64, 1016, 1920, pixel, screens->loseScreen);
		drawHeader(alp, pixel);
		sleep(2);
		pressAnyButton();
	}
}

void screenMenu(GameState *gamestate, Pixel *pix)
{

	int numOfButtons = 16; // number of buttons on snes
	int i;
	int status = 1;
	int start = 0;
	int quit = 0;

	drawImage(96, 60, 960, 1728, pix, screens->titleMain);

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
					pressed = 1;
					break; // break out of the for loop
				}
			}
		}
		if (i == 4)
		{
			gamestate->scene = 1;
			gamestate->sceneStatus = 1;
			status = 0;
			Wait(500000);
		}
		else if (i == 5)
		{
			drawImage(96, 60, 960, 1728, pix, screens->titleStart);
			start = 1;
			quit = 0;
		}
		else if (i == 6)
		{
			drawImage(96, 60, 960, 1728, pix, screens->titleQuit);
			quit = 1;
			start = 0;
		}
		else if (i == 9)
		{
			if (start == 1)
			{
				gamestate->scene = 1;
				gamestate->sceneStatus = 1;
				status = 0;
			}
			else if (quit == 1)
			{
				clearScreen(pix);
				gamestate->gameOn = 0;
				status = 0;
			}
		}
	}
}

void drawNewScene(GameState *gamestate, Alphabet *alp, Pixel *pixel)
{

	int xSize = X_DIM;
	int ySize = Y_DIM;
	int x;

	int yOff, xOff, bgColour;

	for (int y = 0; y < ySize; y++)
	{
		yOff = y * gridSize;
		for (x = 0; x < xSize; x++)
		{
			xOff = x * gridSize;
			bgColour = getColour(gamestate->bg[y][x]);
			drawBlock(gridSize, gridSize, xOff, yOff, bgColour, pixel);

			// getBackGroundImage(tile, bgPos);
			// drawImage(xOff, yOff, gridSize, gridSize, pixel, tile);
		}
	}

	drawHeader(alp, pixel);
	drawLivesDisplay(gamestate, pixel);
	drawLevelDisplay(gamestate->scene, pixel);
	drawScoreDisplay(gamestate, pixel);
	drawTime(gamestate, pixel);

	// draws the finish line
	drawBlock(gamestate->goal->xSize,
			  gamestate->goal->ySize,
			  gamestate->goal->xPos,
			  gamestate->goal->yPos,
			  gamestate->goal->colour,
			  pixel);

	drawSprite(gamestate->mario->xPos,
			   gamestate->mario->yPos,
			   gridSize,
			   gridSize,
			   pixel,
			   gamestate->mario->imgptr_front, -31505);

	int numOfTrees = gamestate->spritesForScene->trees;
	for (x = 0; x < numOfTrees; x++)
	{
		drawSprite((gamestate->treeSpots + x)->xStart,
				   (gamestate->treeSpots + x)->yStart,
				   gamestate->trees->drawSize,
				   gamestate->trees->drawSize,
				   pixel,
				   gamestate->trees->imgPtr_dark,
				   2016);
	}
}

void stageNavigation(GameState *gamestate, Pixel *pixel, Alphabet *alp)
{
	if (gamestate->sceneStatus == 0) // restart
	{
		if (gamestate->scene == 1)
			initScene1(gamestate);
		else if (gamestate->scene == 2)
			initScene2(gamestate);
		else if (gamestate->scene == 3)
			initScene3(gamestate);
		else if (gamestate->scene == 4)
			initScene4(gamestate);

		drawNewScene(gamestate, alp, pixel);
		drawGameState(pixel, gamestate, gamestate->bg);
	}
	else // unpause
	{
		gamestate->sceneStatus = 1;
		drawNewScene(gamestate, alp, pixel);
		drawGameState(pixel, gamestate, gamestate->bg);
	}
}

void winloseCondCheck(GameState *gamestate, Pixel *pixel)
{
	if (gamestate->loseCond == 1) // ran out of lives
	{
		gamestate->scene = 7;
		return;
	}
	else if (gamestate->loseCond == 2) // ran out of time
	{
		gamestate->scene = 7;
		return;
	}

	if (gamestate->winCond == 1 && gamestate->scene == 1)
	{
		calcScenceEndScore(gamestate, pixel);
		gamestate->scene++;
	}
	else if (gamestate->winCond == 1 && gamestate->scene == 2)
	{
		calcScenceEndScore(gamestate, pixel);
		gamestate->scene++;
	}
	else if (gamestate->winCond == 1 && gamestate->scene == 3)
	{
		calcScenceEndScore(gamestate, pixel);
		gamestate->scene++;
	}
	else if (gamestate->winCond == 1 && gamestate->scene == 4)
	{
		calcScenceEndScore(gamestate, pixel);
		gamestate->scene++;
	}
}

void determineStage()
{
	Pixel *pixel = malloc(sizeof(Pixel));
	GameState *gamestate = malloc(sizeof(GameState));
	Alphabet *alp = malloc(sizeof(Alphabet));
	short int *bgTile = malloc(sizeof(short int) * backgroundSize);

	digitsToDraw = malloc(sizeof(DigitsToDraw));
	screens = malloc(sizeof(Screens));
	// backGrounds = malloc(sizeof(BackGroundImages));

	if (gamestate == NULL ||
		alp == NULL ||
		digitsToDraw == NULL ||
		screens == NULL ||
		// backGrounds == NULL ||
		pixel == NULL || bgTile == NULL)
	{
		printf("failed to allocate memory inside function determineStage, exiting now\n");
		exit(0);
	}

	initAlphabet(alp);
	initDigitsToDraw(digitsToDraw);
	initGameState(gamestate);
	initScreens(screens);
	// initBackgrounds(backGrounds);
	gamestate->scene = 0;
	gamestate->gameOn = 1;

	clearScreen(pixel);

	while (gamestate->gameOn)
	{
		if (gamestate->scene == 0)
		{
			clearScreen(pixel);
			screenMenu(gamestate, pixel);
			initScene1(gamestate);
		}
		else if (gamestate->scene == 1)
		{
			stageNavigation(gamestate, pixel, alp, bgTile);
			winloseCondCheck(gamestate, pixel);
		}
		else if (gamestate->scene == 2)
		{
			stageNavigation(gamestate, pixel, alp, bgTile);
			winloseCondCheck(gamestate, pixel);
		}
		else if (gamestate->scene == 3)
		{
			stageNavigation(gamestate, pixel, alp, bgTile);
			winloseCondCheck(gamestate, pixel);
		}
		else if (gamestate->scene == 4)
		{
			stageNavigation(gamestate, pixel, alp, bgTile);
			winloseCondCheck(gamestate, pixel);
		}
		else if (gamestate->scene == 5) // player has won
		{
			drawWinLose(gamestate, alp, pixel);
			gamestate->scene = 0;
		}
		else if (gamestate->scene == 7)
		{
			// sleep(1);
			drawWinLose(gamestate, alp, pixel);
			gamestate->scene = 0;
		}
	}

	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;

	freeGameStateObjects(gamestate);
	freeDigitsToDrawObjects(digitsToDraw);

	free(alp);
	free(gamestate);
	free(digitsToDraw);
	free(screens);
	// free(backGrounds);

	alp = NULL;
	gamestate = NULL;
	digitsToDraw = NULL;
	screens = NULL;
	// backGrounds = NULL;
}

int main()
{
	// comment
	/* initialize snes contoller*/
	gpioPtr = getGPIOPtr(); // init the virtual base address
	Init_GPIO();			// init the clock, latch, data

	/* initialize + get FBS */

	framebufferstruct = initFbInfo();

	srand(time(NULL)); // init rng
	determineStage();  // start game

	memset(framebufferstruct.fptr, 0, 1);
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

	return 0;
}
