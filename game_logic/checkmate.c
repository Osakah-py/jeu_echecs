# include "movements.h"
# include <stdio.h>

// VARAIBLES GLOBALES --------------------------------------------------------------
external struct piece;


// 0 : le roi ne peut pas se deplacer autour de lui, sinon 1
int can_move_around(struct piece king)
{
    int init_posX = king.posX;
    int init_posY = king.posY;
    int modif[3] = {0, 1, -1}; // on veut avoir toutes les modifs pour avoir les 8 cases autour du roi
    int cond;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(i == 0 && j == 0) // on sait deja que le roi est en echec 
            { 
                continue;
            }
            king.posX = init_posX + modif[i];
            king.posY = init_posY + modif[j];
            //le roi peut bouger sur une case sans danger ?
            if(chessboard_mv[king.posY][king.posX] == '0' && is_king_safe(king)) 
            {
                return 1;
            }
        }
    }

    return 0;
}



// 0 si ce n'est pas un echec et mat
int checkmate(int king_is_white)
{
    if(can_move_around)   
    {
        return 0;
    }

    return 1;
}