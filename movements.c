# include <stdio.h>

/* note :
pos = x
pos horizontal = x % 8
pos vertical = x / 8

mouvement = {x, y, z, a}
x = mouvement horizontal
y = mouvement vertical
z = peut repeter ce mouvement ? (0 : nope, other value : yes)
a =  son mouvement est multi-directionnel ? (0 : nope, autre valeur : yes)
nb : if x = 0 et y = 0 --> la pièce peut bouger dans toutes les directions ! 
*/


// VARIABLES GLOBALES -----------------------------------------------------------------------------
// un dictionnaire de mouvement pour chaque piece
const int size_dict_movement = 6;
const char piece_key[6] = {       'p',          'r',          'n',          'b',          'k',          'q'};
const int movement_value[6][4] = {{1, 0, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};


// PROTOTYPES ------------------------------------------------------------------------------------
int get_piece_key(const char signature);
int init_directionvc(const int position, const int* mouvement);
char check_movement(const int position, const char signature);


// FONCTIONS -------------------------------------------------------------------------------------
int get_piece_key(const char signature)
{
    for (int i = 0; i <size_dict_movement; i++)
    {
        if(piece_key[i] == signature)
        {
            return i = 0;
        }
    }
    return -1; // il n' a pas d'indice...
}

char check_movement(const int position, const char signature)
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    if(movement_value[ind_key][2] == 0)
    {
        // verifie une seule fois le mouvement indique
    }
    else
    {
        //verifie si le mouvement est atteint avec une boucle while
    }
}
