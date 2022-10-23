# include "interface.h"
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
const wchar_t pieces [6][8] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};
const char chessboard[8][8];


// FONCTIONS SECONDAIRES ----------------------------------------------------------------------------------


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
    init_echequier (chessboard);

    //Affichage de l'échequier
    affichage(chessboard);
    
    return 0;
}
