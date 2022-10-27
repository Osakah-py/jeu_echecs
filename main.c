# include "interface.h"
# include "inputs.h"
# include "movements.h"
# include "check.h"
# include "game_data.h"
# include "chessboard_manager.h"
# include "checkmate.h"

/* note : 
'0' --> case vide
'lowercase' --> piece noire
'uppercase' --> piece blanche
'p' --> pion
't' --> tour
'c' --> cavalier
'f' --> fou
'r' --> roi
'd' --> dame
*/


// VARIABLES GLOBALES -------------------------------------------------------------------------------------
extern char chessboard[8][8];

// 0 : noir et 1 : blanc
int current_color;
int oponent_color;


// PROTOTYPES ---------------------------------------------------------------------------------------------

void game_initialization();


// MAIN FONCTION ------------------------------------------------------------------------------------------

int main()
{ 
    game_initialization();

    // Boucle principale
    while(1)
    {
        if (current_color % 2 == 1){
            wprintf(L"---- Trait au blanc ---- \n");
        } else {
            wprintf(L"---- Trait au noir ---- \n");
        }
        
        // Entrée utilisateur
        wprintf(L"Quel pièce voulez vous déplacer ? \n");
        int coordonees_init = input();
        
        // On vérifie que l'entrée est correcte
        int verif;
        verif = detection(coordonees_init / 8, coordonees_init % 8, current_color % 2, chessboard);

        if (verif)
        { 
            // la coordonnee est dans le tableau
            int dest = input();
        
            if(!is_movement_correct(coordonees_init, dest))
            {
                wprintf(_RED_() L"Impossible de déplacer votre pièce ici ! \nRéessayez : \n" _DEFAULT_());
            } 
            else 
            {
                // on est un male alpha donc on fait le mouvement quoi qu'il en advienne 
                make_move(coordonees_init, dest); 

                if(check_king(current_color%2)) // 1 : blanc et 0 : noir
                {
                    wprintf(_RED_() L"--- ROI EN ECHEC DONC NON ---\n" _DEFAULT_());
                    undo_move(); // mince, c'est pas le bon mvt
                }
                else
                {
                    clear(); // On reset l'affichage
                    affichage(chessboard, dest); // On affiche l'échiquier
                    oponent_color = (current_color+1) % 2;

                    if(check_king(oponent_color)) // le roi adverse est en echec ?
                    {
                        wprintf(_RED_() L"--- LE ROI EST EN ECHEC ---\n" _DEFAULT_());
                        
                        if(is_checkmate(oponent_color))
                        {
                            wprintf(_RED_() L"--- ECHEC ET MAT ---\n" _DEFAULT_());
                            
                            return 0;
                        }
                    }

                    current_color ++; // On passe au tour suivant
                }
            }
        } 
    }

    return 0;
}



// FONCTIONS ---------------------------------------------------------------------------------------------

void game_initialization()
{
    // INTITIALISATION DES CONSOLES
    #if defined(_WIN32)
        // On passe la console Windows en Unicode 
        _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
      
    #elif defined(__linux__)
        // On passe la console Linux en Unicode
        setlocale(LC_CTYPE, "");    
    #endif
            
    // Initialisation de l'échéquier et des pieces 
    init_echequier(chessboard);

    current_color = 1; //  les blancs commencent
    //Affichage de l'échequier une première fois
    affichage(chessboard, -1); // -1 car on ne veut rien en bleu
}