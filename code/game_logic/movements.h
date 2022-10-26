#ifndef movements 
#define movements
# include <ctype.h>
# include <stdio.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

// on actualise l'echiquier propose
void update_chessboard(const int position, const int destination, char chessboard[8][8]);

// faux --> 0 et vrai --> autres valeurs
int check_movement(const int position, const int destination, const char signature, const char tableau[8][8]); 

// faux --> 0 et vrai --> autres valeurs
int check_king(int is_white);

#endif