# include "data.h"
# include "movements.h"
//juste pour debug
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
/* NB : pour la suite, le fait que les x y sont positives sera tres important !!!
(surtout pour check les mouvements) */
const int movement_value[6][4] = {{0, 1, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};
extern char chessboard_logic[8][8];

extern piece bKing;
extern piece wKing;


// b = black et w = white, on peut accéder simplement la position des roi sans parcourir chessboard_logic


// FONCTIONS -------------------------------------------------------------------------------------
void update_chessboard(const int position, const int destination, char chessboard[8][8])
{
    chessboard[VPOS(destination)][HPOS(destination)] = chessboard[VPOS(position)][HPOS(position)];
    chessboard[VPOS(position)][HPOS(position)] = '0';    
}

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
        if (posX >= 0 && posX < 8 && posY >= 0 && posX < 8) // on verifie si la piece ne sort pas de l'echiquier
        {
            return posX + posY * 8;
        }
        return -1; // elle sort !
    }

    if(position > destination)
    {
        while(posX + posY * 8 > destination) // On veut trouver la position la plus proche vers destination
        {
            if (posX < 0 && posX >= 8 && posY < 0 && posX >= 8) // la piece sort de l'echequier
            {
                return position;
            }
            if (chessboard_logic[posY][posX] != '0')
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
        while(posX + posY * 8 < destination)
        {
            // le signe de x et y sont bien definis dans find_final_move
            if (posX < 0 && posX >= 8 && posY < 0 && posX >= 8)
            {
                return position;
            }
            if(chessboard_logic[posY][posX] != '0')
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

    int inter_pos = find_final_pos(position, destination, movement_adjusted);
    
    if(inter_pos == destination)
    {
        return destination;
    }
    // deux autres cas pour la piece (0, 0) : vertical et hoziontal  
    else if(movement[0] == 0 && movement[1] == 0) 
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


// On actualise la position du roi, si c'en est un !
void update_king_pos(const int position, const char signature)
{
        if (signature == 'r')
    {
        bKing.posX = HPOS(position);
        bKing.posY = VPOS(position);
    }
    if (signature == 'R')
    {
        wKing.posX = HPOS(position);
        wKing.posY = VPOS(position);
    }
}


int check_movement(const int position, const int destination, const char signature, const char tableau[8][8])
{
    if(position == destination) // on ne peut pas se manger !!!
    {
        return 0;   
    }
    
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    duplicate_chessboard(chessboard_logic, tableau); // on actualise l'echiquier 
    const char target = chessboard_logic[VPOS(destination)][HPOS(destination)];
    int pos_tmp;

    // le pion a des movements speciaux a traiter a part
    if (signature == 'p' || signature == 'P') 
    {
        pos_tmp = find_final_pos_pawn(position, destination, signature, target);
        if(pos_tmp == destination)
        {
            return 1;
        }
    }
    
    pos_tmp = find_pos_controller(position, destination, movement_value[ind_key], signature);

    if (pos_tmp == destination)
    {
        // on update l'echiquier localement dans la logique pour voir d'eventuels echecs !
        update_king_pos(destination, signature);
        update_chessboard(position, destination, chessboard_logic); 
        if(check_king(isupper(signature)))
        {
            wprintf(L"ton roi est en echec !\n");
            update_king_pos(position, signature); // le roi revient à sa position initiale
            return 0;
        }
        
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









