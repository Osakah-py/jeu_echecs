# include "game_data.h"
# include "logic_data.h" 
# include "chessboard_manager.h"
# include "check.h"
# include "special_movements.h"

#include <ctype.h>
#include <stdlib.h>
# include <wchar.h>

// VARIABLES GLOBALES ----------------------------------------------------------------------------

extern char chessboard[8][8];
extern int has_wking_moved; // on veut savoir si le roi a bouge ou non pour le roque
extern int has_bking_moved; 

// le pion a avance de deux cases au dernier tour ?
int pawn_move_twice = 0;
int twice_posX = -1;  // la position x du pion concerne 
char twice_signature; // la signature du pion concerne
// NB : pas d'ambiguite sur la couleur car on reset tout si qln n'a pas fait cette action 

extern int two_moves_in_once; // = 1 si un deuxieme mouvement est enregistre dans le meme tour


// FONCTIONS -------------------------------------------------------------------------------------

// PAWN SECTION ----------------------------------------------------------------------------------

int diagonale_mvt(const int position, const int destination, const char signature)
{
    if(isupper(signature))
    {
        // la piece peut se deplacer en diagonale "sans sortir" de l'echiquier  
        if( (position-1 + 1*8 == destination && HPOS(position) != 0) 
         || (position+1 + 1*8 == destination && HPOS(position) != 7) )
        {
            return 1;
        }
    }
    else
    {
        if( (position-1 - 1*8 == destination && HPOS(position) != 0) 
         || (position+1 - 1*8 == destination && HPOS(position) != 7) )
        {
            return 1;
        }
    }
    return 0;
}


int en_passant(const int position, const int destination, const char signature)
{
    int dest_posX = HPOS(destination);
    int enemy_posY;
    char enemy_pawn;

    if(isupper(signature))
    {
        enemy_posY = 4;
        enemy_pawn = 'p';
    }
    else
    {
        enemy_posY = 3;
        enemy_pawn = 'P';
    }
    
    if(pawn_move_twice && dest_posX == twice_posX && VPOS(position) == enemy_posY
        && chessboard[enemy_posY][dest_posX] == enemy_pawn) // on verifie egalement que le pion existe
    {
        pawn_move_twice = 0; // on reinitialise
        // la case d'arrivee du pion est vide donc on supprime le pion adverse 
        make_move(destination, dest_posX + enemy_posY*8); 
        two_moves_in_once = 1; // on a ici deux coups a faire pour un tour (il reste le pion a bouger)
        return 1; // il peut manger en passant !
    }
    
    return 0;
}


// revoie la position final du pion destination sinon -1 (pas de mvt speciaux)
int special_mvt_pawn(const int position, const int destination, const char signature, const char target) 
{
    if(twice_signature == signature)
    {
        pawn_move_twice = 0; // le pion qui a bouge de deux ne peut plus etre mange donc on oublie son mouvement
    }

    // le pion peut manger en diagonale
    if (diagonale_mvt(position, destination, signature))
    {
        if (target == '0')
        {
            if (en_passant(position, destination, signature))
            {
                return destination; // il peut manger en passant !
            }
            else
            {
                return -1; // un pion ne mange pas s'il y a rien :D
            }
        }

        return destination; 
    }
    // le pion peut avancer de deux cases au début
    else if ( (isupper(signature) && position/8 == 1 && (position + 2*8) == destination)
          || (!isupper(signature) && position/8 == 6 && (position - 2*8) == destination) )
    {
        if(target != '0')
        {
            return -1;  // ne peut pas manger une piece comme ca :(
        }

        pawn_move_twice = 1; // le premier mvt du pion est deux cases !
        twice_posX = HPOS(position); // on enregistre son abscisse         
        twice_signature = signature; 
        return destination;
    }
    return -1; // pas mouvements speciaux trouves
}


// KING SECTION ----------------------------------------------------------------------------------

// on va voir si le roque est possible
// on sait que soit la position du roi est soit (4;0) soit (4;7)
int can_castle(const int pos_king, const int posX_rook, const char rook_signature)
{
    int factor_castle;
    if(chessboard[VPOS(pos_king)][posX_rook] == rook_signature) // la tour est la pour effectuer le roque !
    {

        // roque a l'aile roi
        if (posX_rook == 7)
        {
            factor_castle = 1;
        }
        else
        {
            factor_castle = -1;
        }
        // pas besoin de verifier la validite de sa destination finale (verif par movements.c)
        if(!move_and_check(pos_king, pos_king + 1 * factor_castle, rook_signature))
        {
            return 0; // le movement n'est pas valide
        }
        // on va effectuer deux mouvements en un coup ici !
        make_move(posX_rook + VPOS(pos_king) * 8, pos_king + 2*factor_castle - factor_castle * 1);
        two_moves_in_once = 1;
        return 1;
    }   

    return 0;
}


// retourne la position du roi apres avoir analyser le roque desire 
int find_final_mvt_castle(const int position, const int destination, const char signature)
{
    char rook_ally;
    int posX_rook;

    if (isupper(signature))
    {
        rook_ally = 'T';
    }
    else 
    {
        rook_ally = 't';
    }
    // on verifie si la destination est coherente avec le roque
    if (VPOS(position) != VPOS(destination)) 
    {
        return -1; 
    }

    if (HPOS(destination) == 6) // roque a l'aile roi
    {
        posX_rook = 7;
    }
    else if (HPOS(destination) == 2) // roque a l'aile dame
    {
        posX_rook = 0;
    }
    else
    {
        return -1; // ce n'est pas la bonne destination pour un roque
    }

    if(can_castle(position, posX_rook, rook_ally))
    {
        return destination;
    }

    return -1; // on ne peut pas faire le roque
}


// GLOBAL SECTION ----------------------------------------------------------------------------------


int is_special_mvt_correct(const int position, const int destination, const char signature, const char target)
{
    // le pion a des movements speciaux a traiter a part
    if (signature == 'p' || signature == 'P') 
    {
        return special_mvt_pawn(position, destination, signature, target);    
    }
    // idem pour le roi
    else if ( (signature == 'r' && !has_bking_moved) || (signature == 'R' && !has_wking_moved))
    {
        return find_final_mvt_castle(position, destination, signature);
    }

    two_moves_in_once = 0; // on a alors pas 2 coups a jouer dans le meme tour
    return -1; // aucun mouvement special a effectuer

}