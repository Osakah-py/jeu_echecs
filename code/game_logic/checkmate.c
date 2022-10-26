# include "data.h"
# include "movements.h"
# include "check.h"
# include "chessboard_manager.h"
# include <stdio.h>

// VARIABLES GLOBALES --------------------------------------------------------------
extern char chessboard_logic[8][8];
int position[16];


// FONCTIONS -------------------------------------------------------------------------------


// On veut savoir si on peut manger la piece ennemi pour eviter un echec et mat
// On considere que enemy_pos a ete bien actualise avant (puisque le roi a ete en echec)
// Pareil pour position (dans is_checkmate)
int can_eat_enemy(int enemy_pos)
{
    for (int i = 0; i < 16; i++)
    {
        if(check_movement(position[i], enemy_pos, chessboard_logic[VPOS(enemy_pos)][HPOS(enemy_pos)], chessboard_logic))
        {
            return 1; // on peut le manger !
        }
    }
    return 0;
}

// 0 : le roi ne peut pas se deplacer autour de lui et les pieces ne peuvent pas le proteger, sinon 1
int check_around(const int position, const char signature)
{
    int new_pos;
    int new_posX;
    int new_posY;
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
            new_posX = init_posX + modif[i];
            new_posY = init_posY + modif[j];
            // on verifie que la piece ne sorte pas de l'echiquier
            if(check_out_of_range(new_posX, new_posY)) 
            {
                continue;
            }
            
            new_pos = new_posX + new_posY * 8;
            
            // le roi peut bouger sur une case sans danger ?
            if(check_movement(position, new_pos, signature, chessboard_logic)) 
            {
                return 1;
            }
            else // on check si les allies peuvent sauver le roi autour
            {
                for (int i = 0; i < 16; i++)
                {
                    //if(check_movement(position)) 
                }
            }
            // On pense a revenir a la situation actuelle
            update_move_chessboard(position, position, chessboard_logic);
        }
    }

    return 0;
}


// On suppose que le roi est deja en echec et la fct renvoie 0 si ce n'est pas un echec et mat 
int is_checkmate(const int is_king_white, int enemy_pos)
{
    int king_position;
    char king_signature;
    if(is_king_white)
    {
        king_signature = 'R';
    }
    else
    {
        king_signature = 'r';
    }
    king_position = find_king_pos(king_signature);
    collect_allies(position, is_king_white); // On trouve les pieces de la meme couleur
    
    if(check_around(king_position, king_signature))   
    {
        return 0;
    }
    if(can_eat_enemy(enemy_pos))
    {
        return 0;
    }
    return 1;
}