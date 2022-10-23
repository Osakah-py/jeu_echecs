# include <stdio.h>
# include <ctype.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

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
int repeat_move(const int position, const int destination, const movement[2]);
int multidirectionnal(int position, const int destination, const movement[2]);
int direction_move(const int position, const int destination, const int movement[4]); // -1
int check_movement(int position, const int destination, const char signature); // faux --> 0 et vrai --> autres valeurs


// FONCTIONS -------------------------------------------------------------------------------------
int get_piece_key(const char signature)
{
    for (int i = 0; i <size_dict_movement; i++)
    {
        if (piece_key[i] == signature || toupper(piece_key[i]) == signature)
        {
            return i;
        }
    }
    return -1; // il n'a pas d'indice...
}

int repeat_move(const int position, const int destination, const movement[2])
{
    while(0)
    {

    }
}

int multidirectionnal(const int position, const int destination, const int movement[3])
{
    const int init_posH = HPOS(position);
    const int init_posV = VPOS(position);
    const int dest_posH = HPOS(destination);
    const int dest_posV = VPOS(destination);
    if(movement[2] == 0)
    {
        return -1;
    }
    if (init_posH - movement[0] > dest_posH  &&  init_posV - movement[1] > dest_posV)
    {
        // la piece est en haut a droite de la destination
        return (position - movement[0] - movement[1] * 8); 
    }
    if (init_posH - movement[0] > dest_posH  &&  init_posV + movement[1] < dest_posV)
    {
        // la piece est en bas a droite de la destination
        return(position + movement[1] + movement[0] * 8);
    }
    if (init_posH + movement[0] < dest_posH  &&  init_posV - movement[1] > dest_posV)
    {
        //la piece est en haut a gauche de la destination
        return(position - movement[0] + movement[1] * 8)
    }
    if (init_posH + movement[0] < dest_posH  &&  init_posV + movement[1] < dest_posV)
    {
        //la piece est en bas a gauche de la destination
        return (position - movement[0] + movement[1] * 8)
    }
    return -1;
}

int direction_move(int position, const int destination, const int movement[4])
{
    int movement_adjusted[4] = movement; 
    position = multidirectionnal(position, destination, movement_default);
    if (movement[3] != 0 && position == -1) // la pièce est multi-directionnelle
    {
        //on ajuste movement pour l'adapter a multidirectionnal
    movement_adjusted[0] = movement[1];
    movement_adjusted[1] = movement[0]; // on inverse pour avoir toutes les possibilites
    multidirectionnal(position, destination, movement_default);
    }
    return position; // le mouvement ne peut pas aller au-dela de la destination    
}



int check_movement(int position, const int destination, const char signature, char tableau[8][8])
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    const char target = tableau[HPOS(destination)][VPOS(destination)];

    // Il faut check le cas ou le pion peut manger en diagonale (peut-etre une fonction a part)
    if ((signature = 'p' || signature = 'P') 
        && (position-1 + 1*8 == destination || position+1 + 1*8 == destination) )
    {
        if(target == '0')
        {
            return 0; // un pion ne mange pas s'il y a rien :D
        }
        position = destination;
    }
    else
    {
        position = direction_move(position, destination, movement_value[ind_key])
    }

    if (position == destination)
    {
        if (target == '0')
        {
            return 1;
        }
        // les deux pieces ne sont pas de meme couleur
        else if ( isupper(signature) && !isupper(target)
                || !isupper(signature) && isupper(target) )
        {
            // noter la piece mangee 
            return 1;            
        }
    }

    return 0;
}
