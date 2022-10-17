# include <stdio.h>
struct piece
{
    int x;
    int y;
    char signature;
};

typedef struct piece Bishop;

//prototype
void check_piece(struct piece);
