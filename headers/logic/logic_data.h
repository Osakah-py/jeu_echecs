#ifndef logic_data
#define logic_data

# include <stdio.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

extern int pos_enemy;
extern int two_moves_in_once;
extern int has_king_moved;

#endif
