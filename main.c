# include "interface.h"
# include "inputs.h"
# include "movements.h"

/* note : 
'0' --> case vide
'lowercase' --> piece noire
'uppercase' --> piece blanche
'p' --> pawn
'r' --> rook
'n' --> knight
'b' --> bishop
'k' --> king
'q' --> queen
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
    int trait = 1; // trait au blac

    //Affichage de l'échequier une première fois
    affichage(chessboard);

    // Boucle principale
    while(1){
    
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
                update_chessboard(pos, dest, chessboard);
                affichage(chessboard);
                trait ++;
            }
        } 
    }
    return 0;
}