# include "game_data.h"
# include "logic_data.h"
# include "chessboard_manager.h"
# include "movements.h"
# include "check.h"

# include <ctype.h>
# include <wchar.h>


// VARIABLES GLOBALES --------------------------------------------------------------

// variables pour savoir la derniere modif de chessboard
char elt_moved;
char elt_replaced;
int pos_init;
int pos_dest;

// varaibles pour une deuxieme modif de chessboard
char elt_moved2;
char elt_replaced2;
int pos_init2;
int pos_dest2;

extern int two_moves_in_once;
extern char chessboard[8][8];


// FONCTIONS -----------------------------------------------------------------------

int is_same_color(const char p1, const char p2)
{
    if( (isupper(p1) && isupper(p2)) || (islower(p1) && islower(p2)) )
    {
        return 1;
    }
    // pas de la meme couleur T-T (no racismo)
    return 0;
}


int check_out_of_range(const int posX, const int posY)
{
    if(posX < 0 || posX >= 8 || posY < 0 || posY >= 8)
    {
        return 1;
    }
    return 0;
}


int find_king_pos(const char signature)
{
    for (int i = 0; i < 8; i ++)
    {
        for (int j = 0; j < 8; j ++)
        {
            if(chessboard[i][j] == signature)
            {
                return j + i * 8;
            }
        }
    }

    return -1; // bizarre qu'il n'y a pas de roi 
}


void reset_allies(int pos_allies[16])
{
    for (int i = 0; i < 16; i++)
    {
        pos_allies[i] = -1;
    }
}


// On recupere un ensemble de pieces alliees 
void collect_allies(int pos_pieces_allies[16], const char signature_ally)
{
    reset_allies(pos_pieces_allies); // on reset les pos des allies
    char element;
    int ind_array = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j ++)
        {
            element = chessboard[i][j];   
            if(is_same_color(element, signature_ally)) // on a trouve un allie
            {
                pos_pieces_allies[ind_array] = j + i * 8;
                ind_array ++;
            }

            if(ind_array == 16) // on a rempli au maximum notre tableau !
            {
                return;
            }
        }
    }
}


void make_move(const int position, const int destination)
{
    if(two_moves_in_once)
    {
        pos_init2 = position;
        pos_dest2 = destination;
        elt_moved2 = chessboard[VPOS(position)][HPOS(position)];
        elt_replaced2 = chessboard[VPOS(destination)][HPOS(destination)];
    }
    else
    {
        pos_init = position;
        pos_dest = destination;
        elt_moved = chessboard[VPOS(position)][HPOS(position)];
        elt_replaced = chessboard[VPOS(destination)][HPOS(destination)];
    }

    chessboard[VPOS(destination)][HPOS(destination)] = chessboard[VPOS(position)][HPOS(position)];
    chessboard[VPOS(position)][HPOS(position)] = '0';    
}
 
void undo_move()
{    
    if(two_moves_in_once)
    {
        chessboard[VPOS(pos_init2)][HPOS(pos_init2)] = elt_moved2;
        chessboard[VPOS(pos_dest2)][HPOS(pos_dest2)] = elt_replaced2;    
    }    
    
    two_moves_in_once = 0; // il n'y a plus de deux mouvements en un

    chessboard[VPOS(pos_init)][HPOS(pos_init)] = elt_moved;
    chessboard[VPOS(pos_dest)][HPOS(pos_dest)] = elt_replaced;    
}


// une fonction qui regarde si le mouvement est valide avant et apres son execution
int move_and_check(const int position, const int new_pos, const int is_white)
{
    int tmp = 0;
    if(is_movement_correct(position, new_pos)) 
    {
        make_move(position, new_pos); // faisons le mouvement sur l'echiquier 
        tmp = 1;
        if(check_king(is_white))
        {
            tmp = 0; // movement irrealisable
            undo_move(); 
        }
        // on revient en arriere apres avoir vu une possibilite de s'en sortir !
        undo_move();
    }

    return tmp;
}


// On reset tout au tour suivant
void next_turn_logic()
{
    two_moves_in_once = 0;
    if(elt_moved == 'R' || elt_moved2 == 'R')
    {
        has_wking_moved = 1;
    }
    else if(elt_moved == 'r' || elt_moved2 == 'r')
    {
        has_bking_moved = 1;
    }
    
}