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

GameState *gamestate;		// global gamestate
DigitsToDraw *digitsToDraw; // global struct pointer to draw digits at their correct positions
// BugPositions *bugSpots;		   // global array of bug spots
ItemBlockPositions *itemSpots; // global array of items spots
SpriteCount *numOfSprites;	   // global number of sprites
// static short int **digits;	   // global digits for printing to the screen

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
void drawPauseMenu(GameState *gamestate, int *x, int *y, Mario *m, int *status);
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
	else			   // num is 2
		return 0x0000; // black
}

void checkCollision(int *x, int *y, int *xToCheck, int *yToCheck, int *flag)
{
	if ((*x == *xToCheck) && (*y == *yToCheck))
	{
		*flag = 1;
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
	// delayMicroseconds(*speed);
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
			// -31505 is the background for mario
			if (image[i] != -31505)
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

void drawHeader(Alphabet *word)
{
	int dim = 64; // dimention of each alphabet
	Pixel *pix;
	pix = malloc(sizeof(Pixel));

	/* printing all alphabet for level */
	drawImage(0, 0, dim, dim, pix, word->alpPtr_l);
	// drawImage(64, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(64, 0, dim, dim, pix, word->alpPtr_v);
	// drawImage(128, 0, dim, dim, pix, word->alpPtr_v);
	// drawImage(192, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(128, 0, dim, dim, pix, word->alpPtr_l);
	// drawImage(256, 0, dim, dim, pix, word->alpPtr_l);
	// drawImage(320, 0, dim, dim, pix, word->alpPtr_colon);
	// drawImage(192, 0, dim, dim, pix, word->alpPtr_colon);
	// 256

	/* printing all alphabet for life */
	drawImage(320, 0, dim, dim, pix, word->alpPtr_l);
	drawImage(384, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(448, 0, dim, dim, pix, word->alpPtr_f);
	drawImage(512, 0, dim, dim, pix, word->alpPtr_e);
	// drawImage(576, 0, dim, dim, pix, word->alpPtr_colon);
	// drawImage(448, 0, dim, dim, pix, word->alpPtr_l);
	// drawImage(512, 0, dim, dim, pix, word->alpPtr_i);
	// drawImage(576, 0, dim, dim, pix, word->alpPtr_f);
	// drawImage(640, 0, dim, dim, pix, word->alpPtr_e);
	// drawImage(704, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for score */
	drawImage(704, 0, dim, dim, pix, word->alpPtr_s);
	drawImage(768, 0, dim, dim, pix, word->alpPtr_c);
	drawImage(832, 0, dim, dim, pix, word->alpPtr_o);
	drawImage(896, 0, dim, dim, pix, word->alpPtr_r);
	drawImage(960, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1024, 0, dim, dim, pix, word->alpPtr_colon);
	// drawImage(832, 0, dim, dim, pix, word->alpPtr_s);
	// drawImage(896, 0, dim, dim, pix, word->alpPtr_c);
	// drawImage(960, 0, dim, dim, pix, word->alpPtr_o);
	// drawImage(1024, 0, dim, dim, pix, word->alpPtr_r);
	// drawImage(1088, 0, dim, dim, pix, word->alpPtr_e);
	// drawImage(1152, 0, dim, dim, pix, word->alpPtr_colon);

	/* printing all alphabet for time */
	drawImage(1408, 0, dim, dim, pix, word->alpPtr_t);
	drawImage(1472, 0, dim, dim, pix, word->alpPtr_i);
	drawImage(1536, 0, dim, dim, pix, word->alpPtr_m);
	drawImage(1600, 0, dim, dim, pix, word->alpPtr_e);
	drawImage(1664, 0, dim, dim, pix, word->alpPtr_colon);

	free(pix);
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
		{
			// gs->marioGotHit = 1;
			gs->mario->gotHit = 1;
			// printf("bug hit mario ");
		}
		if ((*xD == gs->mario->xPrev) && (*yD == gs->mario->yPrev))
		{
			// gs->marioGotHit = 1;
			gs->mario->gotHit = 1;
			// printf("bug hit mario ");
		}
	}
}

// void drawBugs(Pixel *pixel, BugSprite *bug, GameState *gs)
void drawBugs(Pixel *pixel, GameState *gs)
{
	int i, colour, currentShift, moveD;
	int xD, yD, xPrev, yPrev;
	int bugsToPrint = numOfSprites->bugs;
	BugSprite *bug = gs->bugs;
	// int offSet = gridSize;
	for (i = 0; i < bugsToPrint; i++)
	{

		currentShift = (gs->bugSpots + i)->posShift;
		moveD = (gs->bugSpots + i)->moveDirection;
		bugCollision(&xD, &yD, gs);

		findBugCurrentSpot(&xD, &yD, &xPrev, &yPrev, (gs->bugSpots + i));

		currentShift++;

		// repaint where it was first
		colour = getColour(gs->bg[yPrev / gridSize][xPrev / gridSize]);
		drawBlock(gridSize, gridSize, xPrev, yPrev, colour, pixel);
		bugCollision(&xD, &yD, gs);

		if (moveD == 1)
			drawImage(xD, yD, bug->drawSize, bug->drawSize, pixel, bug->imgptr_right);
		else
			drawImage(xD, yD, bug->drawSize, bug->drawSize, pixel, bug->imgptr_left);

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

	while (gamestate->sceneStatus)
	{
		// drawBugs(pixel, gamestate->bugs, gamestate);
		drawBugs(pixel, gamestate);
	}
	free(pixel);

	pthread_exit(0);
}

void drawItems(Pixel *pixel, ItemBlock *itm, GameState *gs)
{
	int numOfItems = numOfSprites->items;
	int i, xD, yD;
	for (i = 0; i < numOfItems; i++)
	{
		xD = (itemSpots + i)->xStart;
		yD = (itemSpots + i)->yStart;
		int j = (itemSpots + i)->drawFace;
		// xD = 704;
		// yD = 704;
		if (j == 0)
		{
			drawImage(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_F);
		}
		else if (j == 1)
		{
			drawImage(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_s1);
		}
		else if (j == 2)
		{
			drawImage(xD, yD, itm->drawSize, itm->drawSize, pixel, itm->valPtr_s2);
		}

		j++;
		if (j == 3)
			j = 0;
		(itemSpots + i)->drawFace = j;
	}
	Wait(100000);
}

void *valuePackThread(void *param)
{
	GameState *gamestate = (GameState *)param;
	Pixel *pix = malloc(sizeof(Pixel));
	while (gamestate->sceneStatus)
	{
		drawItems(pix, gamestate->itemblocks, gamestate);
	}
	free(pix);

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

	while (gamestate->timeLeft != -1 && gamestate->sceneStatus)
	{
		drawTime(gamestate, pix);
		sleep(1);
		gamestate->timeLeft -= 1;
	}
	free(pix);
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

void drawLevelDisplay(int *scene, Pixel *pixel)
{
	int grdsz = digitsToDraw->lvlDraw->gridSize;
	int x = digitsToDraw->lvlDraw->xPos;
	int y = digitsToDraw->lvlDraw->yPos;
	drawImage(x, y, grdsz, grdsz, pixel, *(digitsToDraw->digits + *scene));
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
	drawScoreDisplay(gamestate, pixel);
}

void didMarioCollideWithAnything(int *xD, int *yD, GameState *gs)
{
	// bug x and y positions ( move and previous )
	int bX, bY, bxP, byP;
	int j;

	// test first if mario collided with bugs
	for (j = 0; j < numOfSprites->bugs; j++)
	{
		// findBugCurrentSpot(&bX, &bY, &bxP, &byP, (bugSpots + j));
		findBugCurrentSpot(&bX, &bY, &bxP, &byP, (gs->bugSpots + j));
		// checkCollision(xD, yD, &bX, &bY, &(gs->marioGotHit));
		// checkCollision(xD, yD, &bxP, &byP, &(gs->marioGotHit));
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
}

void drawPauseMenu(GameState *gamestate, int *x, int *y, Mario *m, int *status)
{
	Pixel *pix = malloc(sizeof(Pixel));
	Pixel *blk = malloc(sizeof(Pixel));
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
			status = 0;
			gamestate->sceneStatus = 1;
			sleep(1);
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
				paused = 0;
			}
			else if (quit == 1)
			{
				paused = 0;
				gamestate->scene = 0;
				gamestate->sceneStatus = 0;
			}
		}
	}
	free(pix);
	free(blk);
}
void testForCollisions(Mario *mario,
					   int *xD,
					   int *yD,
					   Pixel *pixel,
					   GameState *gs,
					   int *status,
					   int *press)
{
	if (gs->mario->gotHit == 1)
	{

		gs->mario->canGetHit = 0;
		int l = gs->lives;
		l--;
		gs->lives = l;

		// redraw where mario is atm as background
		int colour = getColour(gs->bg[*yD / gridSize][*xD / gridSize]);
		drawBlock(mario->drawSize, mario->drawSize, *xD, *yD, colour, pixel);

		*xD = mario->xStart;
		*yD = mario->yStart;
		gs->mario->xPos = *xD;
		gs->mario->yPos = *yD;
		gs->mario->xPrev = *xD;
		gs->mario->yPrev = *yD;

		drawImage(*xD, *yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front);

		gs->mario->gotHit = 0;
		gs->mario->canGetHit = 1;

		if (gs->lives >= 0)
			drawLivesDisplay(gs, pixel);
	}
	else // check goal
	{
		if ((*xD >= gs->goal->xPos) &&
			(*xD <= (gs->goal->xPos + gs->goal->xSize)) &&
			(*yD >= gs->goal->yPos) &&
			(*yD <= (gs->goal->yPos + gs->goal->ySize)))
		{
			*status = 0;
		}
	}
}

void drawGameState(Pixel *pixel,
				   // Sprite *currentSprite,
				   GameState *gamestate,
				   Pixel *block,
				   int bg[Y_DIM][X_DIM])
{
	Mario *mario = gamestate->mario;
	int status = 1;			// game status
	int numOfButtons = 16;	// number of buttons on snes
	int xD = mario->xStart; // move in x direction
	int yD = mario->yStart; // move in y direction

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t bugThread;
	pthread_t timeT;
	pthread_t itemThread;

	pthread_create(&bugThread, &attr, drawBugsAtPos, gamestate);
	pthread_create(&itemThread, &attr, valuePackThread, gamestate);
	pthread_create(&timeT, &attr, timerThread, gamestate);

	// press: for knowing which button was pressed
	// i: for tracking the buttons
	// speed: for holding the time delay to simulate speed ups and downs
	int press, i, speed;
	// speed = baseSpeed * 4;
	// speed = baseSpeed;
	while (status && gamestate->sceneStatus)
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

				if ((i >= 4 || i <= 8) && *(globalButtons + i) == 0)
				{
					// printf("%d was pressed", i);
					pressed = 1;
					press = i;
					break; // break out of the for loop
				}
				// test if anything collided during reading input
			}
		}

		// gamestate->mario->xPrev = xD;
		// gamestate->mario->yPrev = yD;
		mario->xPrev = xD;
		mario->yPrev = yD;
		getCartSpeed(&speed, &xD, &yD, gamestate->bg);			  // determine the speed
		determineButtonPressed(press, &xD, &yD, &status, &speed); // find which direction mario should go

		// gamestate->mario->xPos = xD;
		// gamestate->mario->yPos = yD;
		mario->xPos = xD;
		mario->yPos = yD;

		didMarioCollideWithAnything(&xD, &yD, gamestate);
		delayMicroseconds(speed); // delay to make it seem likes the cart moves slower

		repaint(press, xD, yD, block, gamestate->bg);
		testForCollisions(mario, &xD, &yD, pixel, gamestate, &status, &press);

		if (i == 4)
		{
			pthread_cancel(bugThread);
			pthread_cancel(timeT);
			pthread_cancel(itemThread);
			sleep(1);
			drawPauseMenu(gamestate, &xD, &yD, mario, &status);
			continue;
		}
		else if (press == 5)
			drawImage(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_back);
		else if (press == 6)
			drawImage(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_front);
		else if (press == 7)
			drawImage(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_left);
		else if (press == 8)
			drawImage(xD, yD, mario->drawSize, mario->drawSize, pixel, mario->imgptr_right);
	}
	if (status == 0)
	{
		pthread_cancel(bugThread);
		pthread_cancel(timeT);
		pthread_cancel(itemThread);
	}

	pthread_join(bugThread, NULL);
	pthread_join(timeT, NULL);
	pthread_join(itemThread, NULL);
}

/* Draw a pixel */
void drawPixel(Pixel *pixel)
{
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) +
						(pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}

void screenMenu(int *game)
{
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

	drawImage(0, 0, 1024, 1920, pix, menuPtr);

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
		if (i == 5)
		{
			drawImage(0, 0, 1024, 1920, pix, startPtr);
			start = 1;
			quit = 0;
		}
		else if (i == 6)
		{
			drawImage(0, 0, 1024, 1920, pix, quitPtr);
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
				drawBlock(1920, 1024, 0, 0, 0x0000, pix);
				(*game) = 0;
				status = 0;
			}
		}
	}
}

void drawNewScene(GameState *gamestate, Alphabet *alp)
{
	int xSize = X_DIM;
	int ySize = Y_DIM;
	Pixel *pixel = malloc(sizeof(Pixel));
	int yOff, xOff;
	for (int y = 0; y < ySize; y++)
	{
		yOff = y * gridSize;
		for (int x = 0; x < xSize; x++)
		{
			xOff = x * gridSize;
			int colour = getColour(gamestate->bg[y][x]);
			drawBlock(gridSize, gridSize, xOff, yOff, colour, pixel);
		}
	}
	drawHeader(alp);
	drawLivesDisplay(gamestate, pixel);
	// drawImage(384, 0, 64, 64, pixel, *(digits + *stage)); // draws the current stage
	drawLevelDisplay(&(gamestate->scene), pixel);
	drawScoreDisplay(gamestate, pixel);

	// draws the finish line
	drawBlock(gamestate->goal->xSize,
			  gamestate->goal->ySize,
			  gamestate->goal->xPos,
			  gamestate->goal->yPos,
			  gamestate->goal->colour,
			  pixel);
	drawImage(gamestate->mario->xPos,
			  gamestate->mario->yPos,
			  gridSize,
			  gridSize,
			  pixel,
			  gamestate->mario->imgptr_front);

	// int bugsInScene = numOfSprites->bugs;
	int bugsInScene = gamestate->spritesForScene->bugs;
	int i;
	for (i = 0; i < bugsInScene; i++)
	{
		// drawImage(bugSpots->xStart,
		// 		  bugSpots->yStart,
		// 		  gridSize,
		// 		  gridSize,
		// 		  pixel,
		// 		  gamestate->bugs->imgptr_left);
		drawImage(gamestate->bugSpots->xStart,
				  gamestate->bugSpots->yStart,
				  gridSize,
				  gridSize,
				  pixel,
				  gamestate->bugs->imgptr_left);
	}
	free(pixel);
}

void determineStage()
{
	int maxObjects = 15;
	gamestate = malloc(sizeof(GameState));
	digitsToDraw = malloc(sizeof(DigitsToDraw));
	itemSpots = malloc(sizeof(ItemBlockPositions) * maxObjects);
	numOfSprites = malloc(sizeof(SpriteCount));

	gamestate->scene = 0;

	initDigitsToDraw(digitsToDraw);

	Alphabet *alp = malloc(sizeof(Alphabet));

	initAlphabet(alp);

	int gameOn = 1;
	// int i;

	/* initialize a pixel */
	Pixel *pixel;
	Pixel *block;

	pixel = malloc(sizeof(Pixel));
	block = malloc(sizeof(Pixel));
	memset(framebufferstruct.fptr, 0, 1);

	while (gameOn)
	{
		if (gamestate->scene == 0)
		{
			screenMenu(&gameOn);
		}
		else if (gamestate->scene == 1)
		{

			// initScene1(gamestate, bugSpots, itemSpots, numOfSprites);
			initScene1(gamestate, itemSpots, numOfSprites);
			drawNewScene(gamestate, alp);
			drawGameState(pixel, gamestate, block, gamestate->bg);
			calcScenceEndScore(gamestate, pixel);
			gamestate->scene++;
			// stage++;
		}
		else
		{
			initScene2(gamestate);
			gameOn = 0;
		}
	}

	/* free pixel's allocated memory */
	free(pixel);
	free(block);
	free(alp);
	// free(num);
	freeGameStateObjects(gamestate);
	freeDigitsToDrawObjects(digitsToDraw);

	free(numOfSprites);
	free(itemSpots);

	free(gamestate);
	free(digitsToDraw);
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
