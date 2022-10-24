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
int input();

// MAIN FONCTION ------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{ 
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

    //Affichage de l'échequier
    affichage(chessboard);
    //int entree = input_a_deplacer(chessboard, 1);
    //if (entree){
        // Inserer le code de mouvement
        int pos = 0 + 8 * 4;
        int dest = 7 + 8 * 3;
        if(!check_movement(pos, dest, 'r', chessboard))
        {
            wprintf(L"mouvement avorté :(\n");
        }   
        else
        {
            wprintf(L"movement réussi !\n");
        }
    //} 
    return 0;
}