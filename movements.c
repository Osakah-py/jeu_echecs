# include "movements.h"
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
int find_pos_controller(const int position, const int destination, const int movement[4], const char signature);
// revoie 0 si le pion n'est pas dans le cas ou il doit manger en diagonale (yum yum :D)
int diagonale_cond(const int position, const int destination, const char signature);
int find_final_pos_pawn(const int position, const int destination, const char signature, const char target);
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
    // le mouvement ne peut pas etre repete
    if(movement[2] == 0 && (position + movement[0])/8 != position/8)
    {
        return position += (movement[0] + movement[1] * 8);
    }

    if(position > destination)
    {
        while(position > destination) // On veut trouver la position la plus proche vers destination
        {
            if ((position + movement[0])/8 != position/8) // la piece sort de l'echequier
            {
                return position;
            }
            position += (movement[0] + movement[1] * 8);
            if (chessboard_mv[VPOS(position)][HPOS(position)] != '0')
            {
                // la piece a rencontre une autre piece durant son mouvement !
                return -1; 
            }
        }
    }
    else
    {
        while(position < destination)
        {
            // le signe de x et y sont bien definis dans find_final_move
            if ((position + movement[0])/8 != position/8)
            {
                return position;
            }
            position += (movement[0] + movement[1] * 8); 
            if(chessboard_mv[VPOS(position)][HPOS(position)] != '0')
            {
                return -1; 
            }
        }
    }

    return position;
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
    wprintf(L"movH: %d avec le signe de %d\n", final_movement[0], sign_posH);
    wprintf(L"movV: %d avec le signe de %d\n", final_movement[1], sign_posV);
    return move_piece(position, destination, final_movement);
}


int find_pos_controller(const int position, const int destination, const int movement[4], const char signature)
{    
    int movement_adjusted[4] = {movement[0], movement[1], movement[2], movement[3]}; 
    
    if(!isupper(signature)) // la piece est noire ? 
    {
        // la piece a donc un mouvement dans l'autre sens
        wprintf(L"La piece est noire !\n");
        movement_adjusted[0] = - movement[0];
        movement_adjusted[1] = - movement[1];
    }
        if(movement[0] + movement[1] == 0) // on regarde si la piece peut se diriger dans toutes les dir.
    {
        //deplacement en diagonale pour un premier cas
        movement_adjusted[0] = 1; 
        movement_adjusted[1] = 1;
    }

    int inter_pos = find_final_pos(position, destination, movement_adjusted);
    
    if(inter_pos == destination)
    {
        return destination;
    }
    // deux autres cas pour la piece (0, 0) : vertical et hoziontal  
    else if(movement[0] + movement[1] == 0) 
    {
        movement_adjusted[0] = 1;
        movement_adjusted[1] = 0;
        inter_pos = find_final_pos(position, destination, movement_adjusted);
        if(inter_pos == destination) // il a trouve son mvt ?
        {
            return destination;
        }
        movement_adjusted[0] = 0;
        movement_adjusted[1] = 1;
        
        inter_pos = find_final_pos(position, destination, movement_adjusted);
    }
    // la pièce est multi-directionnelle et pas de pos final trouvee
    else if (movement[3] != 0)
    {
        //on swap x et y dans movement_adjusted pour l'adapter a multidirectionnal
        int tmp = movement_adjusted[0];
        movement_adjusted[0] = movement_adjusted[1];
        movement_adjusted[1] = tmp; // on inverse pour avoir toutes les possibilites        
        
        inter_pos = find_final_pos(position, destination, movement_adjusted);
    }

    return inter_pos;
}

int diagonale_cond(const int position, const int destination, const char signature)
{
    if(isupper(signature))
    {
        if( (position-1 + 1*8 == destination && position%8 != 0) 
         || (position+1 + 1*8 == destination && position%8 != 7) )
        {
            return 1;
        }
    }
    else
    {
        if( (position-1 - 1*8 == destination && position%8 != 0) 
         || (position+1 - 1*8 == destination && position%8 != 7) )
        {
            return 1;
        }
    }
    return 0;
}

int find_final_pos_pawn(const int position, const int destination, const char signature, const char target)
{
    // le pion peut manger en diagonale
    if (diagonale_cond(position, destination, signature))
    {
        if(target == '0')
        {
            return -1; // un pion ne mange pas s'il y a rien :D
        }
        return destination;
    }
    // le pion peut avancer de deux cases au début
    else if ( (isupper(signature) && position/8 == 1 && position + 2*8 == destination)
          || (!isupper(signature) && position/8 == 6 && position - 2*8 == destination) )
    {
        if(target != '0')
        {
            return -1;  // ne peut pas manger une piece comme ca :(
        }
        return destination;
    }
    return position; // pas mouvements speciaux trouves
}

int check_movement(int position, const int destination, const char signature, const char tableau[8][8])
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    duplicate_chessboard(chessboard_mv, tableau);
    const char target = chessboard_mv[HPOS(destination)][VPOS(destination)];
    
    // le pion a des movements speciaux a traiter a part
    if (signature == 'p' || signature == 'P') 
    {
        position = find_final_pos_pawn(position, destination, signature, target);
    }
    
    position = find_pos_controller(position, destination, movement_value[ind_key], signature);
    wprintf(L"pos final : %d\n", position);

    if (position == destination)
    {
        if (target == '0') //case vide ! 
        {
            return 1;
        }
        // les deux pieces ne sont pas de meme couleur
        else if ( (isupper(signature) && !isupper(target))
                || (!isupper(signature) && isupper(target)) )
        {
            // noter la piece mangee 
            return 1;            
        }
    }

    return 0;
}


// IS CHECK ---------------------------------------------------------------------------------- 
/*
int is_check(const int position, const int movement[4])
{
    if(0) // s'il y a un check au roi
    {
        return 1;
    }
    return 0;
}
*/
