# include "data.h"
# include <stdlib.h>

const int size_chessboard = 64;

piece *pieces = malloc(size_chessboard * sizeof(*pieces));

void free_pieces()
{
    free(pieces);
}