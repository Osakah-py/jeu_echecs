# include "data.h"
# include "chessboard_manager.h"
# include <ctype.h>
# include <wchar.h>

/* ici on a les fonctions en relation avec chessboard_logic 
pour faciliter la lecture des autres fichiers :D */

int find_king_pos(const char signature)
{
    for (int i = 0; i < 8; i ++)
    {
        for (int j = 0; j < 8; j ++)
        {
            if(chessboard_logic[i][j] == signature)
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
            element = chessboard_logic[i][j];   
            if(element != '0' && isupper(element) && is_uppercase != 0) // les deux sont blancs
            {
                pos_pieces_allies[ind_array] = j + i * 8;
                ind_array ++;
            }
            else if(element != '0' && !isupper(element) && is_uppercase == 0) // les deux sont noirs
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