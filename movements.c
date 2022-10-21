# include <stdio.h>
struct piece
{
    int x;
    int y;
    char signature;
};

typedef struct piece Bishop;

//prototype
char compare_piece(struct piece, struct piece);

char compare_piece(struct piece p1, struct piece p2)
{
    // do some comparison with two pieces :D
}
