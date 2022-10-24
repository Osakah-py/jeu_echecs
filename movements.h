#ifndef movements 
#define movements
# include <ctype.h>
# include <stdio.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

// faux --> 0 et vrai --> autres valeurs
void update_chessboard(const int position, const int destination, cahr chessboard[8][8])
int check_movement(int position, const int destination, const char signature, const char tableau[8][8]); 

#endif