#include "data.h"
#include "piece_manager.h"


void init_pieces(piece *pieces, const char init_chessboard[8][8])
{
    int ind_pieces = 0;
    char element;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            element = init_chessboard[i][j];
            if(element != '0')
            {
                //pieces[ind_pieces].signature = element;
                //pieces[ind_pieces].posX = j;
                //pieces[ind_pieces].posY = i;
                ind_pieces ++;
            }

        }
    }
    
}
