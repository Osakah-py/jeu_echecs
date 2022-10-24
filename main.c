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
char chessboard[8][8];


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
        
    // Initialisation de l'échéquier
    init_echequier(chessboard);

    //Affichage de l'échequier
    affichage(chessboard);
    //int entree = input_a_deplacer(chessboard, 1);
    //if (entree){
        // Inserer le code de mouvement
        int pos = 4 + 8 * 6;
        int dest = 4 + 8 * 4;
        if(!check_movement(pos, dest, 'p', chessboard))
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