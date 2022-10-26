# include "data.h"
# include "movements.h"
# include "check.h"
# include "chessboard_manager.h"
# include <stdio.h>

// VARAIBLES GLOBALES --------------------------------------------------------------
extern char chessboard_logic[8][8];




// On veut savoir si on peut manger la piece ennemi pour eviter un echec et mat
int can_eat_enemy(const int enemy_position)
{

}

// 0 : le roi ne peut pas se deplacer autour de lui, sinon 1
int can_move_around(const int position, const char signature)
{
    int target_position;
    int init_posX = HPOS(position);
    int init_posY = VPOS(position);
    int modif[3] = {0, 1, -1}; // on veut avoir toutes les modifs pour avoir les 8 cases autour du roi
    //int cond;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(i == 0 && j == 0) // on sait deja que le roi est en echec 
            { 
                continue;
            }
            target_position = init_posX + modif[i];
            target_position = init_posY + modif[j];
            //le roi peut bouger sur une case sans danger ?
            if(chessboard_logic[target_position][target_position] == '0' && check_king(isupper(signature))) 
            {
                return 1;
            }
        }
    }

    return 0;
}


// On suppose que le roi est deja en echec et la fct renvoie 0 si ce n'est pas un echec et mat 
int is_checkmate(const int is_king_white, const int pos_enemy)
{
    int king_position;
    char king_signature;
    if(is_king_white)
    {
        king_signature = "R";
    }
    else
    {
        king_signature = 'r';
    }
    king_position = find_king_pos(king_signature);
    if(can_move_around(king_position, king_signature))   
    {
        return 0;
    }
    //if()

    return 1;
}