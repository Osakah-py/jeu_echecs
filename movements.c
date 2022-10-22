# include <stdio.h>
# define Hpos(a) (a % 8) // l'abscisse de la position sur l'echequier
# define Vpos(a) (a / 8) // l'ordonnee ...

/* note :
pos = x
pos horizontal = x % 8
pos vertical = x / 8

mouvement = {x, y, z, a}
x = mouvement horizontal
y = mouvement vertical
z = peut repeter ce mouvement ? (0 : nope, other value : yes)
a =  son mouvement est multi-directionnel ? (0 : nope, autre valeur : yes)
nb : if x = 0 et y = 0 --> la piece peut bouger dans toutes les directions ! 
*/


// VARIABLES GLOBALES -----------------------------------------------------------------------------
// un dictionnaire de mouvement pour chaque piece
const int size_dict_movement = 6;
const char piece_key[6] = {       'p',          'r',          'n',          'b',          'k',          'q'};
const int movement_value[6][4] = {{1, 0, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};
/* NB : pour la suite, le fait que les x y sont positives sera tres important !!!
(surtout pour la fonction one_move) */


// PROTOTYPES ------------------------------------------------------------------------------------
int get_piece_key(const char signature);
int one_move(const int position, const int destination, const int movement[4]); // -1
int check_movement(const int position, const int destination, const char signature); // faux --> 0 et vrai --> autres valeurs


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
    return -1; // il n'a pas d'indice...
}

int one_move(const int position, const int destination, const int movement[4])
{
    int init_posH = posH(position);
    int init_posV = posV(position);
    int dest_posH = posH(destination);
    int dest_posV = posV(destination);

    if (movement[3] == 0)
    {
        if (init_posH < dest_posH && init_posV < dest_posV)
        {
            // il fait le mouvement brute (x et y toujours positifs dans le "dictionnaire"!!!)
        }
        
    }

    return -1; // le mouvement ne peut pas aller au-dela de la destination    
}

int check_movement(const int position, const int destination, const char signature)
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    int inter_pos = position;

    // Il faut check le cas ou le pion peut manger en diagonale (peut-etre une fonction a part)

    if(movement_value[ind_key][2] != 0)
    {
        // le mouvement est repete avec une boucle while
        while(inter_pos != -1)
        {
            inter_pos = one_move(inter_pos, destination, movement_value[ind_key]);
        }
    }
    else
    {
        // le mouvement est repete une seule fois
        inter_pos = one_move(inter_pos, destination, movement_value[ind_key]);
    }
    
    if(inter_pos == destination)
    {
       return 1;
    }
    return 0;
}
