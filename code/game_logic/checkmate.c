# include "logic_data.h"
# include "movements.h"
# include "check.h"
# include "chessboard_manager.h"

# include <wchar.h>

// VARIABLES GLOBALES --------------------------------------------------------------
int pos_ally[16];
extern int pos_enemy;

// FONCTIONS -------------------------------------------------------------------------------

// On veut savoir si on peut manger la piece ennemi pour eviter un echec et mat
// On considere que enemy_pos a ete bien actualise avant (puisque le roi a ete en echec)
// Pareil pour pos_ally (dans is_checkmate)
int can_eat_enemy(const int is_white)
{
    for (int i = 0; i < 16; i++)
    {       
        // si pos_ally[i] == -1 alors cet allie n'existe pas sur l'echiquier
        if (pos_ally[i] != -1 && move_and_check(pos_ally[i], pos_enemy, is_white))
        {
            return 1; // une piece peut le manger !
        }
    }
    return 0;
}

// 0 : le roi ne peut pas se deplacer autour de lui et les pieces ne peuvent pas le proteger, sinon 1
int can_do_smth_around(const int position, const int is_white)
{
    int new_pos;
    int new_posX;
    int new_posY;
    int init_posX = HPOS(position);
    int init_posY = VPOS(position);
    int modif[3] = {0, 1, -1}; // on veut avoir toutes les modifs pour avoir les 8 cases autour du roi

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
            
            new_pos = new_posX + new_posY * 8; // la nouvelle pos_ally calculee
            
            // le roi peut bouger sur une case sans danger ?
            if(move_and_check(position, new_pos, is_white))
            {
                return 1; // he oui il peut
            }            

            // on check si les allies peuvent sauver le roi autour de lui
            for (int a = 0; a < 16; a++)
            {
                if (pos_ally[a] != -1 && move_and_check(pos_ally[a], new_pos, is_white))
                {
                    return 1;
                } 
            }
            
        }
    }

    return 0; // le roi est bien coince autour de lui...
}


// On suppose que le roi est deja en echec et la fct renvoie 0 si ce n'est pas un echec et mat 
int is_checkmate(const int is_king_white)
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
    collect_allies(pos_ally, king_signature); // On trouve les pieces de la meme couleur
    if(can_do_smth_around(king_position, is_king_white))   
    {
        return 0;
    }
    if(can_eat_enemy(is_king_white))
    {
        return 0;
    }

    return 1;
}