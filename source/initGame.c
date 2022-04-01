#include "initGame.h"
#include "sprites.h"
#include "backgrounds.h"
#include "alphabet.h"
#include "numeric.h"

#include <stdio.h>
#include <stdlib.h>

void initMario(Mario *mario)
{

    int x = 192;
    int y = 128;
    mario->moveSpeed = baseSpeed;
    mario->imgptr_right = (short int *)marioImgs.right_data;
    mario->imgptr_left = (short int *)marioImgs.left_data;
    mario->imgptr_front = (short int *)marioImgs.front_data;
    mario->imgptr_back = (short int *)marioImgs.back_data;
    mario->xStart = x;
    mario->yStart = y;
    mario->xPos = x;
    mario->yPos = y;
    mario->xPrev = x;
    mario->yPrev = y;
    mario->drawSize = gridSize;
    mario->canGetHit = 1;
    mario->gotHit = 0;
}

void initBug(BugSprite *bug)
{
    bug->imgptr_left = (short int *)bugImg.left_data;
    bug->imgptr_right = (short int *)bugImg.right_data;
    bug->drawSize = gridSize;
    bug->moveSpeed = baseSpeed;
}

void initItemBlock(ItemBlock *itemblock)
{
    itemblock->drawSize = gridSize;
    itemblock->itemsDropped = 3; // 4 items are dropped by an item block
    itemblock->valPtr_F = (short int *)ValuePackImg.packf_data;
    itemblock->valPtr_s1 = (short int *)ValuePackImg.packs1_data;
    itemblock->valPtr_s2 = (short int *)ValuePackImg.packs2_data;
}

void initGoalPost(GoalPost *goal)
{
    goal->xSize = 5;
    goal->ySize = 96;
    goal->xPos = 1792;
    goal->yPos = 704;
    goal->colour = 0xFF00;
}

void changeItemAtPos(int i, int xS, int yS, ItemBlockPositions *itemblocks)
{
    (itemblocks + i)->xStart = xS;
    (itemblocks + i)->yStart = yS;
    (itemblocks + i)->drawFace = 0;
}

void changeBugsAtPos(int i,
                     int xS,
                     int yS,
                     int posS,
                     int maxPosS,
                     int moveD,
                     int moveV,
                     BugPositions *bugspot)
{
    (bugspot + i)->xStart = xS;
    (bugspot + i)->yStart = yS;
    (bugspot + i)->posShift = posS;
    (bugspot + i)->moveVector = moveV;
    (bugspot + i)->maxPosShift = maxPosS;
    (bugspot + i)->moveDirection = moveD;
}

void initScene1(GameState *gamestate,
                ItemBlockPositions *itemSpots,
                SpriteCount *numOfSprites)
{
    int maxBugs = 15;
    int maxItemBlocks = 25;
    int i, j;
    // number of sprites to be in this scene
    numOfSprites->bugs = 3;
    numOfSprites->items = 1;

    // 1). i -> position in the struct array
    // 2). xS -> x start pos
    // 3). yS -> y start pos
    // 4). posS -> pos shift (inital position shift, will increment / decrement later) (0 is default)
    // 5). maxPosS -> the maximum the bug can move
    // 6). moveD -> move direction
    // 7). moveV -> up / down (2), left / right (1)
    changeItemAtPos(0, 704, 704, itemSpots);

    // init important game state stuff
    gamestate->timeLeft = 300;
    gamestate->lives = 5;
    gamestate->score = 0;
    gamestate->loseCond = 0;
    gamestate->winCond = 0;

    gamestate->sceneStatus = 1;
    gamestate->scene = 1;

    // gamestate->marioGotHit = 0;
    // init mario

    // init sprite count for each scene
    gamestate->spritesForScene = malloc(sizeof(SpriteCount));
    gamestate->spritesForScene->bugs = 3;
    gamestate->spritesForScene->items = 1;

    gamestate->mario = malloc(sizeof(Mario));
    initMario(gamestate->mario);

    // init other sprites
    gamestate->bugs = malloc(sizeof(BugSprite));
    initBug(gamestate->bugs);
    // changeBugsAtPos(0, 320, 320, 0, 12, -1, 1, bugspots);
    // changeBugsAtPos(1, 480, 544, 0, 10, 1, 2, bugspots);
    // changeBugsAtPos(2, 1088, 160, 0, 25, 1, 2, bugspots);

    gamestate->itemblocks = malloc(sizeof(ItemBlock));
    initItemBlock(gamestate->itemblocks);

    // init the goal post
    gamestate->goal = malloc(sizeof(GoalPost));
    initGoalPost(gamestate->goal);

    gamestate->bugSpots = malloc(sizeof(BugPositions) * maxBugs);
    changeBugsAtPos(0, 320, 320, 0, 12, -1, 1, gamestate->bugSpots);
    changeBugsAtPos(1, 480, 544, 0, 10, 1, 2, gamestate->bugSpots);
    changeBugsAtPos(2, 1088, 160, 0, 25, 1, 2, gamestate->bugSpots);

    gamestate->itemSpots = malloc(sizeof(ItemBlockPositions) * maxItemBlocks);
    changeItemAtPos(0, 704, 704, gamestate->itemSpots);

    // copy background 1 into the gamestate
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg1[i][j];
        }
    }
}

void initScene2(GameState *gamestate)
{
    // copy background 2 into the gamestate
    gamestate->timeLeft = 200;
    int i, j;
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg1[i][j];
        }
    }
}

void freeGameStateObjects(GameState *gamestate)
{
    // free everything in the gamestate object
    free(gamestate->mario);
    free(gamestate->bugs);
    free(gamestate->itemblocks);
    free(gamestate->goal);
    free(gamestate->bugSpots);
    free(gamestate->itemSpots);
    free(gamestate->spritesForScene);
}

void initAlphabet(Alphabet *alp)
{
    alp->alpPtr_c = (short int *)alpImgs.c_data;
    alp->alpPtr_e = (short int *)alpImgs.e_data;
    alp->alpPtr_f = (short int *)alpImgs.f_data;
    alp->alpPtr_i = (short int *)alpImgs.i_data;
    alp->alpPtr_l = (short int *)alpImgs.l_data;
    alp->alpPtr_m = (short int *)alpImgs.m_data;
    alp->alpPtr_o = (short int *)alpImgs.o_data;
    alp->alpPtr_r = (short int *)alpImgs.r_data;
    alp->alpPtr_s = (short int *)alpImgs2.s_data;
    alp->alpPtr_t = (short int *)alpImgs2.t_data;
    alp->alpPtr_v = (short int *)alpImgs2.v_data;
    alp->alpPtr_colon = (short int *)alpImgs2.colon_data;
}

void initNumeric(Numeric *num)
{
    num->numPtr_0 = (short int *)numImgs.zero_data;
    num->numPtr_1 = (short int *)numImgs.one_data;
    num->numPtr_2 = (short int *)numImgs.two_data;
    num->numPtr_3 = (short int *)numImgs.three_data;
    num->numPtr_4 = (short int *)numImgs.four_data;
    num->numPtr_5 = (short int *)numImgs2.five_data;
    num->numPtr_6 = (short int *)numImgs2.six_data;
    num->numPtr_7 = (short int *)numImgs2.seven_data;
    num->numPtr_8 = (short int *)numImgs2.eight_data;
    num->numPtr_9 = (short int *)numImgs2.nine_data;
}

void fillDigitArray(short int **digit)
{
    // short int **digit;
    // Numeric *num = malloc(sizeof(Numeric));

    *(digit + 0) = (short int *)numImgs.zero_data;
    *(digit + 1) = (short int *)numImgs.one_data;
    *(digit + 2) = (short int *)numImgs.two_data;
    *(digit + 3) = (short int *)numImgs.three_data;
    *(digit + 4) = (short int *)numImgs.four_data;
    *(digit + 5) = (short int *)numImgs2.five_data;
    *(digit + 6) = (short int *)numImgs2.six_data;
    *(digit + 7) = (short int *)numImgs2.seven_data;
    *(digit + 8) = (short int *)numImgs2.eight_data;
    *(digit + 9) = (short int *)numImgs2.nine_data;

    // return digit;
}

void freeDigitsToDrawObjects(DigitsToDraw *dtd)
{
    free(dtd->livesDraw);
    free(dtd->timeDraw);
    free(dtd->scoreDraw);
    free(dtd->lvlDraw);
    free(dtd->digits);
}
void initDigitsToDraw(DigitsToDraw *dtd)
{
    dtd->livesDraw = malloc(sizeof(DigitPosition));
    dtd->timeDraw = malloc(sizeof(DigitPosition));
    dtd->scoreDraw = malloc(sizeof(DigitPosition));
    dtd->lvlDraw = malloc(sizeof(DigitPosition));
    dtd->digits = malloc(sizeof(short int *) * 10); // size of 10 because there are 10 digits

    // init lvl digit display
    // dtd->lvlDraw->xPos = 256;
    dtd->lvlDraw->xPos = 192;
    dtd->lvlDraw->yPos = 0;
    dtd->lvlDraw->gridSize = 64;

    // init lives digits display
    // dtd->livesDraw->xPos = 640;
    dtd->livesDraw->xPos = 576;
    dtd->livesDraw->yPos = 0;
    dtd->livesDraw->gridSize = 64;

    // init time digit display
    dtd->timeDraw->xPos = 1728;
    dtd->timeDraw->yPos = 0;
    dtd->timeDraw->gridSize = 64;

    dtd->scoreDraw->xPos = 1088;
    dtd->scoreDraw->yPos = 0;
    dtd->scoreDraw->gridSize = 64;

    fillDigitArray(dtd->digits);
}