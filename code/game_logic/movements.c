# include "game_data.h"
# include "logic_data.h"
# include "special_movements.h"
# include "movements.h"
# include "chessboard_manager.h"

# include <wchar.h>

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
const char piece_key[6] = {       'p',          't',          'c',          'f',          'r',          'd'};
const int movement_value[6][4] = {{0, 1, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};
/* NB : pour la suite, le fait que les x y sont positives sera tres important !!!
(surtout pour check les mouvements) */

extern char chessboard[8][8];

// FONCTIONS -------------------------------------------------------------------------------------

// On trouve le mouvement d'une seule piece

int get_ind_key(const char signature)
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


int move_piece(const int position, const int destination, const int movement[4])
{
    const int movX = movement[0]; 
    const int movY = movement[1];
    int posX = HPOS(position);   
    int posY = VPOS(position);
    // le mouvement ne peut pas etre repete
    posX += movX;
    posY += movY;
    if (movement[2] == 0)
    {
        if (!check_out_of_range(posX, posY)) // on verifie si la piece ne sort pas de l'echiquier
        {
            return posX + posY * 8;
        }
        return -1; // elle sort !
    }

    if(position > destination)
    {
        while (posX + posY * 8 > destination) // On veut trouver la position la plus proche vers destination
        {
            if (check_out_of_range(posX, posY)) // la piece sort de l'echequier
            {
                return -1; // il atteindra jamais la destination alors
            }
            if (chessboard[posY][posX] != '0')
            {
                // la piece a rencontre une autre piece durant son mouvement !
                return -1; 
            }
            posX += movX;
            posY += movY;
        }
    }
    else
    {
        while (posX + posY * 8 < destination)
        {
            // le signe de x et y sont bien definis dans find_final_move
            if (check_out_of_range(posX, posY))
            {
                return -1;
            }
            if(chessboard[posY][posX] != '0')
            {
                return -1; 
            }
            posX += movX;
            posY += movY;
        }
    }

    return posX + posY * 8;
}


void adjust_move_dir(const int position, const int destination, int movement[4])
{    
    int sign_posH = 0;
    int sign_posV = 0;

    if(movement[3] != 0) // la piece est multidirectionnelle ?
    {
        // on veut savoir la position relative de la piece par rapport a la destination
        sign_posH = HPOS(destination) - HPOS(position); 
        sign_posV = VPOS(destination) - VPOS(position); 
    }

    if(sign_posH * movement[0] < 0) // si sign_posH = 0, on garde la valeur initiale
    {
        movement[0] *= -1; // la position relative et le mouvement x doit etre reajuste
    }
    if(sign_posV * movement[1] < 0) // si sign_posV = 0, on garde la valeur initiale
    {
        movement[1] *= -1;
    }
} 


int find_pos_controller(const int position, const int destination, const int movement[4], const char signature)
{    
    int movement_adjusted[4] = {movement[0], movement[1], movement[2], movement[3]}; 
    
    if(!isupper(signature)) // la piece est noire ? 
    {
        // la piece a donc un mouvement dans l'autre sens
        movement_adjusted[0] = - movement[0];
        movement_adjusted[1] = - movement[1];
    }
        if(movement[0] == 0 && movement[1] == 0) // on regarde si la piece peut se diriger dans toutes les dir.
    {
        //deplacement en diagonale pour un premier cas
        movement_adjusted[0] = 1; 
        movement_adjusted[1] = 1;
    }

    // On fait en sorte que le movement "pointe" vers la destination
    adjust_move_dir(position, destination, movement_adjusted);
    int pos_tmp = move_piece(position, destination, movement_adjusted);
    
    if(pos_tmp == destination)
    {
        return destination;
    }
    // deux autres cas pour la piece (0, 0) : vertical et hoziontal  
    else if(movement[0] == 0 && movement[1] == 0) 
    {
        movement_adjusted[0] = 1;
        movement_adjusted[1] = 0;

        adjust_move_dir(position, destination, movement_adjusted);
        int pos_tmp = move_piece(position, destination, movement_adjusted);

        if(pos_tmp == destination) // il a trouve son mvt ?
        {
            return destination;
        }
    }
    // la pièce est multi-directionnelle et pas de pos final trouvee
    if (movement[3] != 0)
    {
        //on swap x et y dans movement_adjusted pour l'adapter a multidirectionnal
        int tmp = movement_adjusted[0];
        movement_adjusted[0] = movement_adjusted[1];
        movement_adjusted[1] = tmp; // on inverse pour avoir toutes les possibilites        

        adjust_move_dir(position, destination, movement_adjusted);
        int pos_tmp = move_piece(position, destination, movement_adjusted);

        if(pos_tmp == destination)
        {
            return destination;
        }
    }

    return -1; // aucun mvt correct n'a ete trouver
}


// 0 : impossible d'effectuer le mouvement sinon tout va bien 
// On suppose que position et destination sotn bien définis
int is_movement_correct(const int position, const int destination)
{
    const char signature = chessboard[VPOS(position)][HPOS(position)];
    const char target = chessboard[VPOS(destination)][HPOS(destination)];

    // on est pas cannibal par ici (+ des cas evidents a traiter)
    if(position == destination || signature == '0' || is_same_color(target, signature)) 
    {
        return 0;   
    }
    const int ind_key = get_ind_key(signature); // cherche le mouvement de la piece
    // on actualise l'echiquier reel et virtuel 
    int pos_tmp = -1;

    // on regarde si il y a un mvt special a traiter
    pos_tmp = special_mvt_controller(position, destination, signature, target);

    wprintf(L"position_th : %d\n", special_mvt_controller(position, destination, signature, target));

    if (pos_tmp != destination) // la piece n'a pas de mouvements speciaux a effectuer
    {
        pos_tmp = find_pos_controller(position, destination, movement_value[ind_key], signature);
    }
    
    if (pos_tmp == destination)
    {
        return 1; // le mouvement est valide !
    }

    return 0;

}