#include "initGame.h"
#include "sprites.h"
#include "backgrounds.h"
#include "alphabet.h"
#include "numeric.h"

#include <stdio.h>
#include <stdlib.h>

void initMario(Mario *mario)
{
    mario->moveSpeed = baseSpeed;
    mario->speedBonus = 0;
    mario->imgptr_right = (short int *)marioImgs.right_data;
    mario->imgptr_left = (short int *)marioImgs.left_data;
    mario->imgptr_front = (short int *)marioImgs.front_data;
    mario->imgptr_back = (short int *)marioImgs.back_data;
    mario->drawSize = gridSize;

    // for handling getting hit by bugs
    mario->canGetHit = 1;
    mario->gotHit = 0;

    // for handling value packs
    mario->didHitPack = 0;
    mario->packCollidedWith = -1; // set to -1 to say didnt collide with an item

    // for handling coins
    mario->didGetCoin = 0;
    mario->coinGotten = -1;
}

void changeMarioPosScene(Mario *mario, int x, int y)
{
    mario->xStart = x;
    mario->yStart = y;
    mario->xPos = x;
    mario->yPos = y;
    mario->xPrev = x;
    mario->yPrev = y;
    mario->speedBonus = 0;
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
    itemblock->valPtr_F = (short int *)ValuePackImg.packf_data;
    itemblock->valPtr_s1 = (short int *)ValuePackImg.packs1_data;
    itemblock->valPtr_s2 = (short int *)ValuePackImg.packs2_data;
}

void initCoin(Coin *coin)
{
    coin->drawSize = gridSize;
    coin->coinPtr_side = (short int *)CoinImg.cside_data;
    coin->coinPtr_left = (short int *)CoinImg.cleft_data;
    coin->coinPtr_front = (short int *)CoinImg.cfront_data;
    coin->coinPtr_right = (short int *)CoinImg.cright_data;
}

void initGoalPost(GoalPost *goal)
{
    goal->xSize = 5;
    goal->ySize = 96;
    goal->xPos = 1792;
    goal->yPos = 704;
    goal->colour = 0xFF00;
}

void initTrees(Tree *t)
{
    t->imgPtr_dark = (short int *)treeImg.darktree_data;
    t->imgPtr_dead = (short int *)treeImg.deadtree_data;
    t->imgPtr_light = (short int *)treeImg.greentree_data;
}

void changeTreePos(int i, int x, int y, TreePositions *trees)
{
    (trees + i)->xStart = x;
    (trees + i)->yStart = y;
}

void changeCoinAtPos(int i, int xS, int yS, CoinPositions *coinposition)
{
    (coinposition + i)->xStart = xS;
    (coinposition + i)->yStart = yS;
    (coinposition + i)->drawFace = 0;
    (coinposition + i)->isVisible = 1;
}

void changeItemAtPos(int i, int xS, int yS, ItemBlockPositions *itemblocks)
{
    (itemblocks + i)->xStart = xS;
    (itemblocks + i)->yStart = yS;
    (itemblocks + i)->drawFace = 0;
    (itemblocks + i)->isVisible = 1;
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

void freeGameStateObjects(GameState *gamestate)
{
    // free everything in the gamestate object
    free(gamestate->mario);
    free(gamestate->bugs);
    free(gamestate->itemblocks);
    free(gamestate->coins);
    free(gamestate->goal);
    free(gamestate->trees);
    free(gamestate->bugSpots);
    free(gamestate->itemSpots);
    free(gamestate->coinSpots);
    free(gamestate->treeSpots);
    free(gamestate->spritesForScene);
}

void initGameState(GameState *gamestate)
{
    int maxBugs = 15;
    int maxItemBlocks = 25;
    int maxCoins = 30;
    int maxTrees = 50;

    gamestate->loseCond = 0;
    gamestate->winCond = 0;

    gamestate->spritesForScene = malloc(sizeof(SpriteCount));

    // init mario
    gamestate->mario = malloc(sizeof(Mario));
    initMario(gamestate->mario);

    // init bug image
    gamestate->bugs = malloc(sizeof(BugSprite));
    initBug(gamestate->bugs);

    // init item block image
    gamestate->itemblocks = malloc(sizeof(ItemBlock));
    initItemBlock(gamestate->itemblocks);

    // init coin image
    gamestate->coins = malloc(sizeof(Coin));
    initCoin(gamestate->coins);

    gamestate->goal = malloc(sizeof(GoalPost));
    initGoalPost(gamestate->goal);

    gamestate->trees = malloc(sizeof(Tree));
    initTrees(gamestate->trees);

    gamestate->bugSpots = malloc(sizeof(BugPositions) * maxBugs);
    gamestate->itemSpots = malloc(sizeof(ItemBlockPositions) * maxItemBlocks);
    gamestate->coinSpots = malloc(sizeof(CoinPositions) * maxCoins);
    gamestate->treeSpots = malloc(sizeof(TreePositions) * maxTrees);
}

void initScene1(GameState *gamestate)

{

    int i, j;

    // 1). i -> position in the struct array
    // 2). xS -> x start pos
    // 3). yS -> y start pos
    // 4). posS -> pos shift (inital position shift, will increment / decrement later) (0 is default)
    // 5). maxPosS -> the maximum the bug can move
    // 6). moveD -> move direction
    // 7). moveV -> up / down (2), left / right (1)
    // changeItemAtPos(0, 704, 704, itemSpots);

    // init important game state stuff
    gamestate->timeLeft = 60;
    gamestate->lives = 5;
    gamestate->score = 0;

    gamestate->sceneStatus = 1;
    gamestate->scene = 1;

    // init sprite count for each scene
    gamestate->spritesForScene->bugs = 3;
    gamestate->spritesForScene->items = 6;
    gamestate->spritesForScene->coins = 6;
    gamestate->spritesForScene->trees = 40;

    changeMarioPosScene(gamestate->mario, 192, 128);

    int yPos = 576;
    int xPos = 160;
    changeBugsAtPos(0, 320, 320, 0, 10, -1, 1, gamestate->bugSpots);
    changeBugsAtPos(1, 480, 544, 0, 10, 1, 2, gamestate->bugSpots);
    changeBugsAtPos(2, 1216, 160, 0, 25, 1, 2, gamestate->bugSpots);

    changeCoinAtPos(0, xPos, yPos, gamestate->coinSpots);
    changeCoinAtPos(1, xPos + gridSize, yPos, gamestate->coinSpots);
    changeCoinAtPos(2, xPos + (2 * gridSize), yPos, gamestate->coinSpots);
    xPos = 704;
    changeCoinAtPos(3, xPos, yPos, gamestate->coinSpots);
    changeCoinAtPos(4, xPos + gridSize, yPos, gamestate->coinSpots);
    changeCoinAtPos(5, xPos + (2 * gridSize), yPos, gamestate->coinSpots);

    xPos = 512;
    yPos = 704;
    changeItemAtPos(0, xPos, yPos, gamestate->itemSpots);
    changeItemAtPos(1, xPos, yPos + gridSize, gamestate->itemSpots);
    changeItemAtPos(2, xPos, yPos + (2 * gridSize), gamestate->itemSpots);
    xPos = 1408;
    yPos = 128;
    changeItemAtPos(3, xPos, yPos, gamestate->itemSpots);
    changeItemAtPos(4, xPos, yPos + gridSize, gamestate->itemSpots);
    changeItemAtPos(5, xPos, yPos + (11 * gridSize), gamestate->itemSpots);

    int numOfTrees = gamestate->spritesForScene->trees;
    int stop = 14;
    int currentTree = 0;
    xPos = 480;
    yPos = 64;
    for (i = 0; i < stop; i++)
        changeTreePos(currentTree, xPos, yPos * (i + 1), gamestate->treeSpots);

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
    gamestate->sceneStatus = 1;
    gamestate->scene = 1;
    changeMarioPosScene(gamestate->mario, 32, 736);
    int i, j;
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg2[i][j];
        }
    }
}

void initScene3(GameState *gamestate)
{
    // copy background 2 into the gamestate
    gamestate->timeLeft = 200;
    int i, j;
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg3[i][j];
        }
    }
}

void initScene4(GameState *gamestate)
{
    // copy background 2 into the gamestate
    gamestate->timeLeft = 200;
    int i, j;
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg4[i][j];
        }
    }
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