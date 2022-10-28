#ifndef logic_data
#define logic_data

# include <stdio.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

extern int pos_enemy;
extern int mvt_enemy[2];

extern int two_moves_in_once;
extern int has_wking_moved;
extern int has_bking_moved;


#endif
