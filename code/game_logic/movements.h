#ifndef movements 
#define movements
# include <ctype.h>
# include <stdio.h>
 

// on actualise l'echiquier propose
void update_move_chessboard(const int position, const int destination, char chessboard[8][8]);

// faux --> 0 et vrai --> autres valeurs
int check_movement(const int position, const int destination, const char signature, const char tableau[8][8]); 

#endif