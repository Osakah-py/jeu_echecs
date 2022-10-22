# include <stdio.h>

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
int main (int argc, char ** argv){  
    char *chessboard = (char *) malloc(sizeof(char) * 8 * 8); //array of a classic chessboard
    init_chessboard(chessboard, size_chessboard);
    return 0;
}
