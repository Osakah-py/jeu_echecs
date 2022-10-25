# include "data.h"
# include <stdlib>

const int size_chessboard = 64;


struct piece
{
    const char signature; // le type de piece
    int posX; // entre 0 et 7
    int posY; // entre 0 et 7
};

struct piece *pieces = (struct pieces *) malloc(sizeof(struct piece) * size_chessboard);

void free_pieces()
{
    free(pieces);
}