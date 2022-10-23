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
/* NB : pour la suite, le fait que les x y sont positives sera tres important !!!
(surtout pour check les mouvements) */
const int movement_value[6][4] = {{1, 0, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};

char chessboard_mv[8][8];


// PROTOTYPES ------------------------------------------------------------------------------------
void duplicate_chessboard(char target[8][8], const char original[8][8]);
int get_piece_key(const char signature);
int move_piece(int position, const int destination, const int movement[3]);
int find_final_pos(int position, const int destination, const int movement[4]);
int find_pos_manager(const int position, const int destination, const int movement[4]); // -1
// renvoie 0 si le mouvement n'est pas valide, sinon 1
int check_movement(int position, const int destination, const char signature, const char tableau[8][8]); // faux --> 0 et vrai --> autres valeurs

int is_check(const int position, const int movement[4]);

// FONCTIONS -------------------------------------------------------------------------------------
void duplicate_chessboard(char target[8][8], const char original[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            target[i][j] = original[i][j];
        }
    }
}


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


int move_piece(int position, const int destination, const int movement[3])
{
    if(movement[3] == 0)
    {
        return position += (movement[0] + movement[1] * 8);
    }
    if(position > destination)
    {
        while(position < destination)
        {
            position += (movement[0] + movement[1] * 8);
            if(chessboard_mv[VPOS(position)][HPOS(position)] != '0')
            {
// la piece a rencontre une autre piece durant son mouvement, qui n'est donc pas valide
                return -1; 
            }
        }
    }
    else
    {
        while(position < destination)
        {
            // le signe de x et y sont bien definis dans find_final_move
            position += (movement[0] + movement[1] * 8); 
            if(chessboard_mv[VPOS(position)][HPOS(position)] != '0')
            {
// la piece a rencontree une autre piece durant son mouvement, qui n'est donc pas valide
                return -1; 
            }
        }
    }

    return position;
}


int find_final_pos(const int position, const int destination, const int movement[4])
{
    const int init_posH = HPOS(position);
    const int init_posV = VPOS(position);
    const int dest_posH = HPOS(destination);
    const int dest_posV = VPOS(destination);
    
    int final_movement[3] = {movement[0], movement[1], movement[2]};
    if (init_posH + movement[0] <= dest_posH  &&  init_posV + movement[1] <= dest_posV)
    {
        //la piece est en bas a gauche de la destination
        return move_piece(position, destination, final_movement);
    }

    if(movement[3] == 0) // la piece ne peut pas etre multidirectionnelle
    {
        if (init_posH - movement[0] >= dest_posH  &&  init_posV - movement[1] >= dest_posV)
        {
            // la piece est en haut a droite de la destination
            final_movement[0] = - movement[0];
            final_movement[1] = - movement[1];
            return move_piece(position, destination, final_movement);
        }
        if (init_posH - movement[0] >= dest_posH  &&  init_posV + movement[1] <= dest_posV)
        {
            // la piece est en bas a droite de la destination
            final_movement[0] = - movement[0];
            return move_piece(position, destination, final_movement);
        }
        if (init_posH + movement[0] <= dest_posH  &&  init_posV - movement[1] >= dest_posV)
        {
            //la piece est en haut a gauche de la destination
            final_movement[1] = - movement[1];
            return move_piece(position, destination, final_movement);
        }
    }

    return -1;
}


int find_pos_controller(int position, const int destination, const int movement[4])
{
    int movement_adjusted[4] = {movement[0], movement[1], movement[2], movement[3]}; 
    position = find_final_pos(position, destination, movement_adjusted);

    // la pièce est multi-directionnelle et pas de pos final trouvee
    if (movement[3] != 0 && position == -1)
    {
        //on ajuste movement pour l'adapter a multidirectionnal
        movement_adjusted[0] = movement[1];
        movement_adjusted[1] = movement[0]; // on inverse pour avoir toutes les possibilites
        find_final_pos(position, destination, movement_adjusted);
    }
    
    return position; // le mouvement ne peut pas aller au-dela de la destination    
}



int check_movement(int position, const int destination, const char signature, const char tableau[8][8])
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    duplicate_chessboard(chessboard_mv, tableau);
    const char target = chessboard_mv[HPOS(destination)][VPOS(destination)];

    // Il faut check le cas ou le pion peut manger en diagonale (peut-etre une fonction a part)
    if ((signature == 'p' || signature == 'P') 
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
        position = find_pos_controller(position, destination, movement_value[ind_key]);
    }

    if (position == destination)
    {
        if (target == '0') //case vide ! 
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


// IS CHECK ---------------------------------------------------------------------------------- 
int is_check(const int position, const int movement[4])
{
    if(0) // s'il y a un check au roi
    {
        return 1;
    }
    return 0;
}
