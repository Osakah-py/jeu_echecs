#ifndef DATA
#define DATA

# include <stdio.h>

typedef struct piece
{
    char signature; // le type de piece
    int posX; // entre 0 et 7
    int posY; // entre 0 et 7
} piece;

piece pieces[64];

void free_pieces();

#endif
