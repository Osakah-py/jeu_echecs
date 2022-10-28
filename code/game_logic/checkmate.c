# include "game_data.h"
# include "logic_data.h"
# include "movements.h"
# include "check.h"
# include "chessboard_manager.h"

# include <wchar.h>

// VARIABLES GLOBALES --------------------------------------------------------------
extern int pos_enemy;
extern int mvt_enemy[2];

// on evite des actualisations de check.c sur pos_enemy pendant des verifs virtuelles
int current_pos_enemy; 
int pos_allies[16];

// FONCTIONS -------------------------------------------------------------------------------


// On veut savoir si une piece alliee peut bloquer une attaque de l'ennemi en annulant l'echec
int can_block_enemy_attack(const int king_pos, const char king_signature, const int mvt[2])
{
    int pos_ally;
    int pos_tmp = current_pos_enemy;

    for (int i = 0; i < 7; i++) // la portee maximale est 7
    {
        pos_tmp += (mvt[0] + mvt[1] * 8);
        //mvt est deja bien defini et la piece met en echec le roi
        // cette cond se realisera 
        if(pos_tmp == king_pos)
        {
            break; 
        }
        for (register int a = 0; a < 16; a++)
        {
            pos_ally = pos_allies[a];
            if(pos_ally != -1 && move_and_check(pos_ally, pos_tmp, isupper(king_signature)))
            {
                return 1; // on peut sauver le roi !    
            }
        }
        
    }
    return 0;
}


// On veut savoir si on peut manger la piece ennemi pour eviter un echec et mat
// On considere que enemy_pos a ete bien actualise avant (puisque le roi a ete en echec)
// Pareil pour pos_allies (dans is_checkmate)
int can_eat_enemy(const int is_white)
{
    for (int i = 0; i < 16; i++)
    {       
        // si pos_allies[i] == -1 alors cet allie n'existe pas sur l'echiquier
        if (pos_allies[i] != -1 && move_and_check(pos_allies[i], current_pos_enemy, is_white))
        {
            return 1; // une piece peut le manger !
        }
    }
    return 0;
}

// 0 : le roi ne peut pas se deplacer autour de lui et les pieces ne peuvent pas le proteger, sinon 1
int can_move_around(const int position, const int is_white)
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
            
            new_pos = new_posX + new_posY * 8; // la nouvelle pos_allies calculee
            
            // le roi peut bouger sur une case sans danger ?
            if(move_and_check(position, new_pos, is_white))
            {
                return 1; // he oui il peut
            }                        
        }
    }

    return 0; // le roi est bien coince autour de lui...
}


// On suppose que le roi est deja en echec et la fct renvoie 0 si ce n'est pas un echec et mat 
int is_checkmate(const int is_king_white)
{
    int current_mvt_enemy[4] = {mvt_enemy[0], mvt_enemy[1]};
    wprintf(L"moveX and moveY enemy : %d %d\n", mvt_enemy[0], mvt_enemy[1]);

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

    current_pos_enemy = pos_enemy; // on fixe la pos de la piece qui menace le roi
    king_position = find_king_pos(king_signature);
    if(can_move_around(king_position, is_king_white))   
    {
        return 0;
    }
    
    if(can_eat_enemy(is_king_white))
    {
        return 0;
    }

    collect_allies(pos_allies, king_signature); // On trouve les pieces de la meme couleur
    wprintf(L"pos ally : %d\n", pos_allies[0]);
    if(can_block_enemy_attack(king_position, king_signature, current_mvt_enemy))
    {
        return 0;
    }

    return 1;
}