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
const int size_chessboard = 64; // 8 * 8  


// FONCTIONS SECONDAIRES ----------------------------------------------------------------------------------


// MAIN FONCTION ------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
        // On passe la console Windows en Unicode  
#if defined(_WIN32)
    _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
    
    // On passe la console Linux en Unicode  
#elif defined(unix)
    //setlocale(LC_CTYPE, "");
#endif
    test();
    return 0;
}
