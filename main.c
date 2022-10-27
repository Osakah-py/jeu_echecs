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

// PROTOTYPES ---------------------------------------------------------------------------------------------


// MAIN FONCTION ------------------------------------------------------------------------------------------

int main()
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

    int trait = 1; // trait au blanc
    int trait_adverse;
    //Affichage de l'échequier une première fois
    affichage(chessboard, -1); // -1 car on ne veut rien en bleu

    // Boucle principale
    while(1)
    {
        if (trait % 2 == 1){
            wprintf(L"---- Trait au blanc ---- \n");
        } else {
            wprintf(L"---- Trait au noir ---- \n");
        }
        
        // Entrée utilisateur
        wprintf(L"Quel pièce voulez vous déplacer ? \n");
        int coordonees_init = input();
        
        // On vérifie que l'entrée est correcte
        int verif;
        verif = detection(coordonees_init / 8, coordonees_init % 8, trait % 2, chessboard);

        if (verif)
        { 
            // la coordonnee est dans le tableau
            int dest = input();
        
            if(!check_movement(coordonees_init, dest))
            {
                wprintf(_RED_() L"Impossible de déplacer votre pièce ici ! \nRéessayez : \n" _DEFAULT_());
            } 
            else 
            {
                // on met a jour le mouvement sur l'échiquier
                make_move(coordonees_init, dest); 
                clear(); // On reset l'affichage
                affichage(chessboard, dest); // On affiche l'échéquier
                
                trait_adverse = (trait+1) % 2;

                if(check_king(trait_adverse)) // le roi adverse est en echec ?
                {
                    wprintf(_RED_() L"--- LE ROI EST EN ECHEC ---\n" _DEFAULT_());
                    
                    if(is_checkmate(trait_adverse))
                    {
                        wprintf(_RED_() L"--- ECHEC ET MAT ---\n" _DEFAULT_());
                        return 0;
                    }
                }
                
                trait ++; // On passe au tour suivant
            }
        } 
    }

    return 0;
}



// FONCTIONS ---------------------------------------------------------------------------------------------
