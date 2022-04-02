#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    short int *alpPtr_c;
    short int *alpPtr_e;
    short int *alpPtr_f;
    short int *alpPtr_i;
    short int *alpPtr_l;
    short int *alpPtr_m;
    short int *alpPtr_o;
    short int *alpPtr_r;
    short int *alpPtr_s;
    short int *alpPtr_t;
    short int *alpPtr_v;
    short int *alpPtr_colon;
} Alphabet;

typedef struct
{
    short int *numPtr_0;
    short int *numPtr_1;
    short int *numPtr_2;
    short int *numPtr_3;
    short int *numPtr_4;
    short int *numPtr_5;
    short int *numPtr_6;
    short int *numPtr_7;
    short int *numPtr_8;
    short int *numPtr_9;
} Numeric;

typedef struct
{
    int xPos, yPos;
    int gridSize;
} DigitPosition;

typedef struct
{
    DigitPosition *timeDraw;
    DigitPosition *scoreDraw;
    DigitPosition *livesDraw;
    DigitPosition *lvlDraw;
    short int **digits;
} DigitsToDraw;

typedef struct
{
    short int *imgptr_front;
    short int *imgptr_back;
    short int *imgptr_right;
    short int *imgptr_left;
} MarioImg;

typedef struct
{
    short int *imgPtr_dark;
    short int *imgPtr_dead;
    short int *imgPtr_light;
} Tree;

typedef struct {
    int xStart;
    int yStart;
} TreePositions;

typedef struct
{
    int drawSize;
    int xStart, yStart;
    int xPos, yPos;
    int moveSpeed, speedBonus;
    short int *imgptr_front;
    short int *imgptr_back;
    short int *imgptr_right;
    short int *imgptr_left;
    int xPrev, yPrev;
    int gotHit, canGetHit;
    int didHitPack, packCollidedWith;
    int didGetCoin, coinGotten;

} Mario;

typedef struct
{
    int drawSize;
    int moveSpeed;
    short int *imgptr_right;
    short int *imgptr_left;

} BugSprite;

typedef struct
{
    int drawSize;
    short int *valPtr_F;
    short int *valPtr_s1;
    short int *valPtr_s2;
} ItemBlock;

typedef struct
{
    int drawSize;
    short int *coinPtr_side;
    short int *coinPtr_left;
    short int *coinPtr_front;
    short int *coinPtr_right;
} Coin;

typedef struct
{
    BugSprite *bugs;
    MarioImg *marioImg;
    ItemBlock *blockImg;

} SpriteImages;

typedef struct
{
    int xStart;
    int yStart;
    int posShift;
    int maxPosShift;
    int moveVector;    // whether right to left (1) or up and down (2)
    int moveDirection; // -1 is opposite what is was previously

} BugPositions;

typedef struct
{

    int xStart;
    int yStart;
    int drawFace;
    int isVisible;
} ItemBlockPositions;

typedef struct
{
    int xStart;
    int yStart;
    int drawFace;
    int isVisible;
} CoinPositions;

typedef struct
{
    int xSize;
    int ySize;
    int colour;
    int xPos;
    int yPos;

} GoalPost;

typedef struct
{
    int bugs;
    int items;
    int coins;
} SpriteCount;

static int Y_DIM = 33; // 33
static int X_DIM = 60; // 60

typedef struct
{
    int bg[33][60]; // background
    Mario *mario;   // mario pointer object
    BugSprite *bugs;
    BugPositions *bugSpots;        // bug positions
    ItemBlockPositions *itemSpots; // item positons
    ItemBlock *itemblocks;
    CoinPositions *coinSpots;
    Coin *coins;
    GoalPost *goal;
    SpriteCount *spritesForScene;
    int winCond, loseCond;
    int lives, score, timeLeft;
    int scene, sceneStatus;
} GameState;

static int baseSpeed = 55000;
static int gridSize = 32;

// static int MAX_BUGS = 15;
// static int MAX_ITEMS = 15;

void initMario(Mario *mario);

void initBug(BugSprite *bug);

void initItemBlock(ItemBlock *itemblock);

void initCoin(Coin *coin);

void initGoalPost(GoalPost *goal);

void changeCoinAtPos(int i, int xS, int yS, CoinPositions *coinposition);

void changeItemAtPos(int i, int xS, int yS, ItemBlockPositions *itemblocks);

void changeBugsAtPos(int i,
                     int xS,
                     int yS,
                     int posS,
                     int maxPosS,
                     int moveD,
                     int moveV,
                     BugPositions *bugspot);

void initScene1(GameState *gamestate);

void initScene2(GameState *gamestate);

void initScene3(GameState *gamestate);

void initScene4(GameState *gamestate);

void freeGameStateObjects(GameState *gamestate);

void initNumeric(Numeric *num);
void initAlphabet(Alphabet *alp);

void fillDigitArray(short int **digit);
void freeDigitsToDrawObjects(DigitsToDraw *dtd);

void initDigitsToDraw(DigitsToDraw *dtd);

void initSpriteImgs(SpriteImages *imgs);

void initDigitsToDraw(DigitsToDraw *dtd);

void initGameState(GameState *gamestate);

void changeMarioPosScene(Mario *mario, int x, int y);
