# include "code/game_logic/data.h"
# include "interface.h"
# include "inputs.h"
# include "code/game_logic/movements.h"
# include "code/game_logic/check.h"

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


// FONCTIONS SECONDAIRES ----------------------------------------------------------------------------------

// MAIN FONCTION ------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{ 
    
    // INTITIALISATION DES CONSOLES
    #if defined(_WIN32)
        // On passe la console Windows en Unicode 
        _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
      
    #elif defined(__linux__)
        // On passe la console Linux en Unicode
        setlocale(LC_CTYPE, "");    
    #endif
    
    char chessboard[8][8];
        
    // Initialisation de l'échéquier
    init_echequier(chessboard);
    int trait = 1; // trait au blanc

    //Affichage de l'échequier une première fois
    affichage(chessboard, -1); // -1 car on ne veut rien en bleu

    // Boucle principale
    while(1){
        if (trait % 2 == 1){
            wprintf(L"---- Trait au blanc ---- \n");
        } else {
            wprintf(L"---- Trait au noir ---- \n");
        }
        // Entrée utilisateur
        wprintf(L"Quel pièce voulez vous déplacer ? \n");
        int coordonees_init = input();
        // On vérifie que l'entrée est correcte
        char piece;
        int verif;
        verif = detection(coordonees_init / 8, coordonees_init % 8, trait % 2, chessboard, &piece);

        if (verif){ // la coordonnee est dans le tableau
            int dest = input();
        
            if(!check_movement(coordonees_init, dest, piece, chessboard))
            {
                wprintf(_RED_() L"Impossible de déplacer votre pièce ici ! \nRéessayez : \n" _DEFAULT_());
            } else {
                
                update_chessboard(coordonees_init, dest, chessboard); // on met a jour l'échiquier
                clear(); // On reset l'affichage
                affichage(chessboard, dest); // On affiche l'échéquier
                
                if(check_king((trait+1) % 2)) // le roi adverse est en echec ?
                {
                    wprintf(_RED_() L"LE ROI EST EN ECHEC\n" _DEFAULT_());
                }
                
                trait ++; // On passe au tour suivant
            }
        } 
    }
    return 0;
}