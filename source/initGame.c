#include "initGame.h"
#include "sprites.h"
#include "backgrounds.h"
#include "alphabet.h"

#include <stdio.h>
#include <stdlib.h>

void initMario(Sprite *mario)
{

    mario->canMove = 1;
    mario->moveSpeed = baseSpeed;
    mario->imgptr_right = (short int *)marioImgs.right_data;
    mario->imgptr_left = (short int *)marioImgs.left_data;
    mario->imgptr_front = (short int *)marioImgs.front_data;
    mario->imgptr_back = (short int *)marioImgs.back_data;
    mario->xStart = 192;
    mario->yStart = 128;
    mario->drawSize = gridSize;
}

void initSpike(Sprite *spike)
{
    spike->canMove = 0;
    spike->moveSpeed = 0;
    spike->drawSize = gridSize;
}

void initScene1(GameState *gamestate)
{
    gamestate->lives = 3;
    gamestate->score = 0;
    gamestate->loseCond = 0;
    gamestate->winCond = 0;
    gamestate->numberOfSprites = 14;

    int i, j;
    for (i = 0; i < Y_DIM; i++)
    {
        for (j = 0; j < X_DIM; j++)
        {
            (*gamestate).bg[i][j] = bg1[i][j];
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