#include "initGame.h"
#include "sprites.h"
#include "backgrounds.h"
#include "alphabet.h"
#include "numeric.h"
#include "winScreen.h"
#include "loseScreen.h"
#include "title.h"
#include "titleStart.h"
#include "titlequit.h"
#include "bgGraphics.h"

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
    goal->xSize = 0;
    goal->ySize = 0;
    goal->xPos = 0;
    goal->yPos = 0;
    goal->colour = 0;
}

void initGoalPostChanged(GoalPost *goal, int xSize, int ySize, int xPos, int yPos, int colour)
{
    goal->xSize = xSize;
    goal->ySize = ySize;
    goal->xPos = xPos;
    goal->yPos = yPos;
    goal->colour = colour;
}

void initTrees(Tree *t)
{
    t->imgPtr_dark = (short int *)treeImg.darktree_data;
    t->imgPtr_dead = (short int *)treeImg.deadtree_data;
    t->drawSize = gridSize;
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

// 1). i -> position in the struct array
// 2). xS -> x start pos
// 3). yS -> y start pos
// 4). posS -> pos shift (inital position shift, will increment / decrement later) (0 is default)
// 5). maxPosS -> the maximum the bug can move
// 6). moveD -> move direction
// 7). moveV -> up / down (2), left / right (1)
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

void makeLineOfTrees(int x, int y, int *curr, int *used, int stop, int d, GameState *gs)
{
    *used += stop;
    for (int i = 0; i < stop; i++)
    {
        if (d == 1)
            changeTreePos(*curr, x, y + (gridSize * i), gs->treeSpots);
        else
            changeTreePos(*curr, x + (gridSize * i), y, gs->treeSpots);
        (*curr)++;
    }
}

void freeGameStateObjects(GameState *gamestate)
{
    // free everything in the gamestate object
    free(gamestate->mario);
    gamestate->mario = NULL;

    free(gamestate->bugs);
    gamestate->bugs = NULL;

    free(gamestate->itemblocks);
    gamestate->itemblocks = NULL;

    free(gamestate->coins);
    gamestate->coins = NULL;

    free(gamestate->goal);
    gamestate->goal = NULL;

    free(gamestate->trees);
    gamestate->trees = NULL;

    free(gamestate->bugSpots);
    gamestate->bugSpots = NULL;

    free(gamestate->itemSpots);
    gamestate->itemSpots = NULL;

    free(gamestate->coinSpots);
    gamestate->coinSpots = NULL;

    free(gamestate->treeSpots);
    gamestate->treeSpots = NULL;

    free(gamestate->spritesForScene);
    gamestate->spritesForScene = NULL;
}

void initGameState(GameState *gamestate)
{
    int maxBugs = 15;
    int maxItemBlocks = 30;
    int maxCoins = 30;
    int maxTrees = 150;

    // gamestate->gameOn = 1;

    gamestate->spritesForScene = malloc(sizeof(SpriteCount));
    if (gamestate->spritesForScene == NULL)
    {
        printf("failed to alloc for spritesForScene, exiting now\n");
        exit(0);
    }

    // init mario
    gamestate->mario = malloc(sizeof(Mario));
    if (gamestate->mario == NULL)
    {
        printf("failed to alloc for mario, exiting now\n");
        exit(0);
    }
    initMario(gamestate->mario);

    // init bug image
    gamestate->bugs = malloc(sizeof(BugSprite));
    if (gamestate->bugs == NULL)
    {
        printf("failed to alloc for bugs, exiting now\n");
        exit(0);
    }
    initBug(gamestate->bugs);

    // init item block image
    gamestate->itemblocks = malloc(sizeof(ItemBlock));
    if (gamestate->itemblocks == NULL)
    {
        printf("failed to alloc for itemblocks, exiting now\n");
        exit(0);
    }
    initItemBlock(gamestate->itemblocks);

    // init coin image
    gamestate->coins = malloc(sizeof(Coin));
    if (gamestate->coins == NULL)
    {
        printf("failed to alloc for coins, exiting now\n");
        exit(0);
    }
    initCoin(gamestate->coins);

    gamestate->goal = malloc(sizeof(GoalPost));
    if (gamestate->goal == NULL)
    {
        printf("failed to alloc for goal, exiting now\n");
        exit(0);
    }
    initGoalPost(gamestate->goal);

    gamestate->trees = malloc(sizeof(Tree));
    if (gamestate->trees == NULL)
    {
        printf("failed to alloc for trees, exiting now\n");
        exit(0);
    }
    initTrees(gamestate->trees);

    gamestate->bugSpots = malloc(sizeof(BugPositions) * maxBugs);
    gamestate->itemSpots = malloc(sizeof(ItemBlockPositions) * maxItemBlocks);
    gamestate->coinSpots = malloc(sizeof(CoinPositions) * maxCoins);
    gamestate->treeSpots = malloc(sizeof(TreePositions) * maxTrees);
    if (gamestate->bugSpots == NULL ||
        gamestate->itemSpots == NULL ||
        gamestate->coinSpots == NULL ||
        gamestate->treeSpots == NULL)
    {
        printf("failed to alloc for sprite locations, exiting now\n");
        exit(0);
    }
}

void initScene1(GameState *gamestate)

{

    int i, j;
    int justUsingStaticToStopWarning = backgroundSize;
    justUsingStaticToStopWarning--;

    // init important game state stuff
    gamestate->loseCond = 0;
    gamestate->winCond = 0;
    gamestate->timeLeft = 60;
    gamestate->lives = 5;
    gamestate->score = 0;

    gamestate->sceneStatus = 1;
    gamestate->scene = 1;

    // init sprite count for each scene
    gamestate->spritesForScene->bugs = 3;
    gamestate->spritesForScene->items = 6;
    gamestate->spritesForScene->coins = 6;
    // gamestate->spritesForScene->trees = 40;

    changeMarioPosScene(gamestate->mario, 192, 128);
    initGoalPostChanged(gamestate->goal, 5, 96, 1792, 704, 0xFF00);

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

    int numOfTreesUsed = 0;

    // 15 trees
    int stop = 15;
    numOfTreesUsed += stop;
    int currentTree = 0;
    xPos = 480;
    yPos = 64;

    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 1, gamestate);

    // // 10 trees
    yPos = 320;
    xPos = 896;
    stop = 10;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    // // 22 trees
    yPos += gridSize;
    stop = 22;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 1, gamestate);

    // // 15 trees
    yPos = 320;
    xPos = 1248;
    stop = 15;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    // // 21
    yPos = 672;
    xPos = 1248;
    stop = 21;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    yPos = 800;
    xPos = 1248;
    stop = 21;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    gamestate->spritesForScene->trees = numOfTreesUsed;
    gamestate->spritesForScene->trees = 0;

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
    gamestate->timeLeft += 30;
    gamestate->sceneStatus = 1;
    gamestate->scene = 2;
    gamestate->loseCond = 0;
    gamestate->winCond = 0;

    changeMarioPosScene(gamestate->mario, 32, 736);
    initGoalPostChanged(gamestate->goal, 5, 128, 1824, 896, 0xFF00);

    gamestate->spritesForScene->coins = 6;
    int yPos = 576;
    int xPos = 128;
    changeCoinAtPos(0, xPos, yPos, gamestate->coinSpots);
    changeCoinAtPos(1, xPos + gridSize, yPos, gamestate->coinSpots);

    xPos = 672;
    yPos -= 64;
    changeCoinAtPos(2, xPos, yPos, gamestate->coinSpots);
    changeCoinAtPos(3, xPos - gridSize, yPos, gamestate->coinSpots);
    changeCoinAtPos(4, xPos - (2 * gridSize), yPos, gamestate->coinSpots);
    changeCoinAtPos(5, xPos + (23 * gridSize), yPos + (8 * gridSize), gamestate->coinSpots);

    gamestate->spritesForScene->items = 6;
    xPos = 512;
    yPos = 704;
    changeItemAtPos(0, xPos - (4 * gridSize), yPos, gamestate->itemSpots);
    changeItemAtPos(1, xPos + (4 * gridSize), yPos + gridSize, gamestate->itemSpots);
    changeItemAtPos(2, xPos + (7 * gridSize), yPos - (19 * gridSize), gamestate->itemSpots);
    xPos = 1408;
    yPos = 128;
    changeItemAtPos(3, xPos + (4 * gridSize), yPos, gamestate->itemSpots);
    changeItemAtPos(4, xPos - (36 * gridSize), yPos + gridSize, gamestate->itemSpots);
    changeItemAtPos(5, xPos + (7 * gridSize), yPos + (11 * gridSize), gamestate->itemSpots);

    gamestate->spritesForScene->trees = 7;
    yPos = 576 - 64;
    xPos = 672 - (7 * gridSize);

    changeTreePos(0, xPos - (gridSize * 2), yPos - (gridSize * 5), gamestate->treeSpots);
    changeTreePos(1, xPos - (gridSize * 1), yPos, gamestate->treeSpots);
    changeTreePos(2, xPos, yPos + (gridSize * 2), gamestate->treeSpots);
    changeTreePos(3, xPos - (gridSize * 3), yPos + (gridSize * 4), gamestate->treeSpots);
    xPos = 1216 - 32;
    yPos = 160;
    changeTreePos(4, xPos, yPos + (gridSize * 2), gamestate->treeSpots);
    changeTreePos(5, xPos, yPos + (gridSize * 11), gamestate->treeSpots);
    changeTreePos(6, xPos, yPos + (gridSize * 20), gamestate->treeSpots);

    gamestate->spritesForScene->bugs = 6;
    changeBugsAtPos(0, 320, 320, 0, 10, -1, 1, gamestate->bugSpots); // stays
    changeBugsAtPos(1, 480, 544, 0, 10, 1, 1, gamestate->bugSpots);  // stays
    changeBugsAtPos(2, 1216, 160, 0, 25, 1, 2, gamestate->bugSpots); // stays
    changeBugsAtPos(3, 1280, 864, 0, 15, 1, 1, gamestate->bugSpots);
    changeBugsAtPos(4, 1344, 480, 0, 25, -1, 1, gamestate->bugSpots);
    changeBugsAtPos(5, 1312, 288, 0, 15, 1, 1, gamestate->bugSpots);

    // gamestate->spritesForScene->items = 6;

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
    changeMarioPosScene(gamestate->mario, 32, 736);
    initGoalPostChanged(gamestate->goal, 5, 96, 96, 128, 0xFF00);

    gamestate->loseCond = 0;
    gamestate->winCond = 0;
    gamestate->timeLeft += 60;
    gamestate->sceneStatus = 1;
    gamestate->scene = 3;

    gamestate->spritesForScene->bugs = 8;
    changeBugsAtPos(0, 384, 928, 0, 42, 1, 1, gamestate->bugSpots);   // stays
    changeBugsAtPos(1, 1728, 960, 0, 35, -1, 1, gamestate->bugSpots); // stays
    changeBugsAtPos(2, 1824, 992, 0, 14, -1, 2, gamestate->bugSpots); // stays
    changeBugsAtPos(3, 1632, 704, 0, 13, -1, 2, gamestate->bugSpots);
    changeBugsAtPos(4, 1536, 736, 0, 35, -1, 1, gamestate->bugSpots);
    changeBugsAtPos(5, 256, 384, 0, 37, 1, 1, gamestate->bugSpots);
    changeBugsAtPos(6, 1312, 608, 0, 5, -1, 1, gamestate->bugSpots);
    changeBugsAtPos(7, 192, 96, 0, 30, 1, 2, gamestate->bugSpots);

    int numOfTreesUsed = 0;
    int currentTree = 0;
    // 3 trees
    int stop = 3;
    numOfTreesUsed += stop;
    // top line
    int xPos = 736;
    int yPos = 896;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 928;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1120;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1312;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1504;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1696;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    // bottom line
    xPos = 864;
    yPos = 992;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1120;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1376;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 1632;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    // last straight line  12 trees
    xPos = 416;
    yPos = 96;
    stop = 2;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 992;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    yPos = 224;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 512;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    xPos = 768;
    yPos = 128;
    makeLineOfTrees(xPos, yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);
    yPos = 192;
    makeLineOfTrees(xPos + (3 * gridSize), yPos, &currentTree, &numOfTreesUsed, stop, 0, gamestate);

    gamestate->spritesForScene->trees = 42;

    gamestate->spritesForScene->items = 6;
    changeItemAtPos(0, 384, 832, gamestate->itemSpots);
    changeItemAtPos(1, 384, 864, gamestate->itemSpots);
    changeItemAtPos(2, 384, 896, gamestate->itemSpots);
    changeItemAtPos(3, 1408, 800, gamestate->itemSpots);
    changeItemAtPos(4, 1824, 256, gamestate->itemSpots);
    changeItemAtPos(5, 288, 160, gamestate->itemSpots);

    gamestate->spritesForScene->coins = 7;
    changeCoinAtPos(0, 1088, 800, gamestate->coinSpots);
    changeCoinAtPos(1, 1248, 544, gamestate->coinSpots);
    changeCoinAtPos(2, 1248, 576, gamestate->coinSpots);
    changeCoinAtPos(3, 1280, 576, gamestate->coinSpots);
    changeCoinAtPos(4, 1216, 576, gamestate->coinSpots);
    changeCoinAtPos(5, 640, 576, gamestate->coinSpots);
    changeCoinAtPos(6, 672, 576, gamestate->coinSpots);

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
    // copy background 2 into the
    gamestate->loseCond = 0;
    gamestate->winCond = 0;
    gamestate->timeLeft += 75;
    gamestate->sceneStatus = 1;
    gamestate->scene = 4;
    gamestate->spritesForScene->trees = 0;

    changeMarioPosScene(gamestate->mario, 1888, 256);
    initGoalPostChanged(gamestate->goal, 5, 64, 64, 960, 0x0FF0);

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
    dtd->livesDraw = NULL;

    free(dtd->timeDraw);
    dtd->timeDraw = NULL;

    free(dtd->scoreDraw);
    dtd->scoreDraw = NULL;

    free(dtd->lvlDraw);
    dtd->lvlDraw = NULL;

    free(dtd->digits);
    dtd->digits = NULL;
}
void initDigitsToDraw(DigitsToDraw *dtd)
{
    dtd->livesDraw = malloc(sizeof(DigitPosition));
    dtd->timeDraw = malloc(sizeof(DigitPosition));
    dtd->scoreDraw = malloc(sizeof(DigitPosition));
    dtd->lvlDraw = malloc(sizeof(DigitPosition));
    dtd->digits = malloc(sizeof(short int *) * 10); // size of 10 because there are 10 digits

    if (dtd->livesDraw == NULL ||
        dtd->timeDraw == NULL ||
        dtd->scoreDraw == NULL ||
        dtd->lvlDraw == NULL ||
        dtd->digits == NULL)
    {
        printf("failed to allocate for digitsToDraw, exiting now\n");
        exit(0);
    }

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

void initScreens(Screens *screen)
{
    screen->winScreen = (short int *)img_win.pixel_data;
    screen->loseScreen = (short int *)img_lose.pixel_data;
    screen->titleMain = (short int *)img_title.pixel_data;
    screen->titleStart = (short int *)img_start.pixel_data;
    screen->titleQuit = (short int *)img_quit.pixel_data;
}

void initBackgrounds(BackGroundImages *bgImg)
{
    bgImg->road = (short int *)img_road.road_stone;
    bgImg->rainbow = (short int *)img_road.road_rainbow;
    bgImg->grass1 = (short int *)img_bg.lightgrass_data;
    bgImg->grass2 = (short int *)img_bg.darkgrass_data;
    bgImg->water = (short int *)img_bg.water_data;
    bgImg->lava = (short int *)img_bg.lava_data;
}