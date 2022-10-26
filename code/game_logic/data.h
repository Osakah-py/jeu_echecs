#ifndef data
#define data

# include <stdio.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

extern char chessboard_logic[8][8];
#endif
