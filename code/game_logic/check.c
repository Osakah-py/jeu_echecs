# include "data.h"
# include "chessboard_manager.h"
# include "check.h"

// IS CHECK ---------------------------------------------------------------------------------- 
extern char chessboard_logic[8][8];


// on suppose que les characteres dans enemies sont en miniscule
void upper_enemies_or_not(const char signature, char *enemies, const int size)
{
    if(!isupper(signature))
    {
        for (int i = 0; i < size; i++)
        {
            enemies[i] = toupper(enemies[i]);
        }
        
    }
}

// pour un mouvement en particulier a partir du roi (0 si le roi est en echec)
int check_moveset(const char signature, const int position, const int movX, const int movY, 
char *enemies, const int nb_enemies, const int range)
{
    const int init_posX = HPOS(position); 
    const int init_posY = VPOS(position); 
    int posX;
    int posY; 
    int movX_bis; 
    int movY_bis; 
    
    //On ajuste enemies par rapport a target
    upper_enemies_or_not(signature, enemies, nb_enemies);
    // On a tout les combinaisons possibles avec movX et movY
    const int move_combo[8][2] = 
    {{movX, movY}, {-movX, -movY}, {movY, movX}, {-movY, -movX},
    {-movX, movY}, {movX, -movY}, {-movY, movX}, {movY, -movX}};

    register char element = '0'; 
    // on part de la cible pour verifier si un ennemi le menace avec movX et movY 
    for (register int a = 0; a < 8; a++)
    {
        posX = init_posX;
        posY = init_posY;
        movX_bis = move_combo[a][0];
        movY_bis = move_combo[a][1];
        // on check jusqu'a la portee desiree
        for (register int j = 0; j < range; j++)
        {    
            posX += movX_bis;
            posY += movY_bis; 
            if(posX < 8 && posY < 8 && posX >= 0 && posY >= 0) // on regarde si on sort de l'echiquier
            {
                element = chessboard_logic[posY][posX];
                if( (isupper(element) && isupper(signature)) 
                 || (!isupper(element) && !isupper(signature)) )
                {
                    break; // le roi est couvert par une piece alliee !
                }
                for (register int i = 0; i < nb_enemies; i++)
                {
                    if(element == enemies[i])
                    {
                        return 0;
                    }
                }
            }
            else
            {
                break; // ca sort de l'echiquier donc on arrete la boucle
            }
        }
    }

    return 1;
}


// Si les pions adverses mettent en danger la cible, alors on revoie 0
int pawn_not_threat_target(const int position, int signature)
{
    const int posX = HPOS(position);
    const int posY = VPOS(position); 
    if( (isupper(signature) && (chessboard_logic[posY+1][posX-1] == 'p' || chessboard_logic[posY+1][posX+1] == 'p'))
     ||(!isupper(signature) && (chessboard_logic[posY-1][posX-1] == 'P' || chessboard_logic[posY-1][posX+1] == 'P')) )
    {
        return 0;
    }
    return 1;
}


// On suppose que chessboard_logic est bien actualise 
int is_king_safe(char king_signature)
{
    const int king_position = find_king_pos(king_signature);
    int tmp;
    char enemies2[2] = {'0','0'};
    char enemy[1] = {'0'};
    
    // On regarde les pieces qui peuvent atteindre horizontalement et verticalement le roi    
    enemies2[0] = 't';
    enemies2[1] = 'd';
    tmp = check_moveset(king_signature, king_position, 1, 0, enemies2, 2, 8);
    if(tmp == 0)
    {
        return 0;
    }  
    // On regarde les pieces qui peuvent atteindre diagonalement le roi    
    enemies2[0] = 'f';
    tmp = check_moveset(king_signature, king_position, 1, 1, enemies2, 2, 8);
    if(tmp == 0)
    {
        return 0;
    }
    // On regarde les cavaliers qui peuvent atteindre le roi    
    enemy[0] = 'c';
    tmp = check_moveset(king_signature, king_position, 2, 1, enemy, 1, 1);
    if(tmp == 0)
    {
        return 0;
    }
    // On regarde les pions qui peuvent atteindre le roi
    tmp = pawn_not_threat_target(king_signature, king_position);
    if(tmp == 0)
    {
        return 0;
    }
    return 1;
}

// 0 : not check
int check_king(const int is_white)
{
    int cond; 
    
    if(is_white)
    {
        cond = is_king_safe('R');
    }
    else
    {
        cond = is_king_safe('r');
    }

    if(cond == 0) // s'il y a un check au roi
    {
        return 1;
    }

    return 0; // il n'y a pas de check
}
