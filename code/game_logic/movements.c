# include "game_data.h"
# include "logic_data.h"
# include "movements.h"
# include "chessboard_manager.h"

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

// On actualise le mouvement d'une seule piece

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


int move_piece(const int position, const int destination, const int movement[3])
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


int find_final_pos(const int position, const int destination, const int movement[4])
{
    // On trouve les coordonnees de position et destination sur l'echequier
    const int init_posH = HPOS(position);
    const int init_posV = VPOS(position);
    const int dest_posH = HPOS(destination);
    const int dest_posV = VPOS(destination);
    
    int final_movement[3] = {movement[0], movement[1], movement[2]};
    int sign_posH = 0;
    int sign_posV = 0;

    if(movement[3] != 0) // la piece est multidirectionnelle ?
    {
        // on veut savoir la position relative de la piece par rapport a la destination
        sign_posH = dest_posH - init_posH; 
        sign_posV = dest_posV - init_posV; 
    }

    if(sign_posH * final_movement[0] < 0) // si sign_posH = 0, on garde la valeur initiale
    {
        final_movement[0] *= -1; // la position relative et le mouvement x doit etre reajuste
    }
    if(sign_posV * final_movement[1] < 0) // si sign_posV = 0, on garde la valeur initiale
    {
        final_movement[1] *= -1;
    }
    return move_piece(position, destination, final_movement);
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

    int pos_tmp = find_final_pos(position, destination, movement_adjusted);
    
    if(pos_tmp == destination)
    {
        return destination;
    }
    // deux autres cas pour la piece (0, 0) : vertical et hoziontal  
    else if(movement[0] == 0 && movement[1] == 0) 
    {
        movement_adjusted[0] = 1;
        movement_adjusted[1] = 0;
        pos_tmp = find_final_pos(position, destination, movement_adjusted);
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
        
        pos_tmp = find_final_pos(position, destination, movement_adjusted);
    }

    return pos_tmp;
}

int diagonale_mvt(const int position, const int destination, const char signature)
{
    if(isupper(signature))
    {
        // la piece peut se deplacer en diagonale "sans sortir" de l'echiquier  
        if( (position-1 + 1*8 == destination && HPOS(position) != 0) 
         || (position+1 + 1*8 == destination && HPOS(position) != 7) )
        {
            return 1;
        }
    }
    else
    {
        if( (position-1 - 1*8 == destination && HPOS(position) != 0) 
         || (position+1 - 1*8 == destination && HPOS(position) != 7) )
        {
            return 1;
        }
    }
    return 0;
}

int special_mvt_pawn(const int position, const int destination, const char signature, const char target) 
{
    // le pion peut manger en diagonale
    if (diagonale_mvt(position, destination, signature))
    {
        if(target == '0')
        {
            return -1; // un pion ne mange pas s'il y a rien :D
        }
        return destination; // on s'en fout de la couleur
    }
    // le pion peut avancer de deux cases au début
    else if ( (isupper(signature) && position/8 == 1 && (position + 2*8) == destination)
          || (!isupper(signature) && position/8 == 6 && (position - 2*8) == destination) )
    {
        if(target != '0')
        {
            return -1;  // ne peut pas manger une piece comme ca :(
        }
        return destination;
    }
    return position; // pas mouvements speciaux trouves
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
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    // on actualise l'echiquier reel et virtuel 
    int pos_tmp = -1;

    // le pion a des movements speciaux a traiter a part
    if (signature == 'p' || signature == 'P') 
    {
        pos_tmp = special_mvt_pawn(position, destination, signature, target);
    
    }
    if (pos_tmp != destination) // le pion n'a pas de mouvement speciaux a effectuer
    {
        pos_tmp = find_pos_controller(position, destination, movement_value[ind_key], signature);
    }
    
    if (pos_tmp == destination)
    {
        return 1; // le mouvement est valide !
    }

    return 0;

}