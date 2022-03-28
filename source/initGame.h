#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int drawSize;
    int xStart;
    int yStart;
    int canMove;
    int moveSpeed;
    short int *imgptr_front;
    short int *imgptr_back;
    short int *imgptr_right;
    short int *imgptr_left;
} Sprite;

typedef struct
{
    int xSize;
    int ySize;
    int colour;

} GoalPost;

static int Y_DIM = 33; // 33
static int X_DIM = 60; // 60

typedef struct
{
    int bg[33][60];
    int numberOfSprites;
    Sprite *mario;
    Sprite *sceneSprites;
    int winCond;
    int loseCond;
    int lives;
    int score;
    time_t timeLeft;
} GameState;

static int baseSpeed = 55000;
static int gridSize = 32;

void initMario(Sprite *mario);

void initSpike(Sprite *spike);

void initScene1(GameState *gamestate);

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