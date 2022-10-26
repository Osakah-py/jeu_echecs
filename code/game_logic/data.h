#ifndef data
#define data

# include <stdio.h>

typedef struct
{
    char signature; // le type de piece
    int posX; // entre 0 et 7
    int posY; // entre 0 et 7
} piece;

extern piece pieces_logic[64];
extern char chessboard_logic[8][8];

extern piece bKing;
extern piece wKing;

#endif
