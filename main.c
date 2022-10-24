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
    
    int y1;
    int x1;
    char piece;
    int entree = input_a_deplacer(chessboard, 0, &y1, &x1, &piece);
    if (entree){
        // Inserer le code de mouvement

        int pos = x1 + 8 * y1;
        int dest = input_ou_deplacer();
        
        wprintf(L"\x1b[31mdest = x:%d y:%d \x1b[39m \n", dest % 8, dest / 8);
        
        if(!check_movement(pos, dest, piece, chessboard))
        {
            wprintf(L"mouvement avorté :(\n");
        }   
        else
        {
            wprintf(L"movement réussi !\n");
        }
    } else {
        wprintf(L"Apprend ou sont tes pions toi");
    }
    return 0;
}