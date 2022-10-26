# include "data.h"
# include "piece_manager.h"
# include <ctype.h>
# include <wchar.h>

/* ici on a les fonctions en relation avec chessboard_logic 
pour faciliter la lecture des autres fichiers :D*/

int find_king_pos(const char signature)
{
    for (int i = 0; i < 8; i ++)
    {
        for (int j = 0; j < 8; j ++)
        {
            if(chessboard_logic[i][j] == 'r')
            {
                return j + i * 8;
            }
            if(chessboard_logic[i][j] == 'R')
            {
                return j + i * 8;
            }
            
        }
    }
}

// On recupere un ensemble de pieces alliees 
void collect_allies(int pos_pieces_allies[16], int is_uppercase)
{
    char element;
    int ind_array = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j ++)
        {
            element = chessboard_logic[i][j]
            if(element != '0' && isupper(element) && is_uppercase != 0)
            {
                pos_pieces_allies[ind_array] = pos;
            }
            else if(element != '0' && !isupper(element) && is_uppercase == 0)
            {
                pos_pieces_allies[ind_array] = pos;
            }

            if(ind_array == 16) // on remplit au maximum notre tableau !
            {
                return;
            }
        }
    }
}