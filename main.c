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
    int y1;
    int x1;
    int entree = input_a_deplacer(chessboard, 0, &y1, &x1);
    if (entree){
        // Inserer le code de mouvement
        char x2 = 'A';
        int y2 = 0;
        scanf("%c%d", &x2, &y2);
        int pos = x1 + 8 * y1;
        int dest = x2 - 1 + 8 * ((int) toupper(y2) - 65);
        
        wprintf(L"dest = x:%d y:%d \n", dest % 8, dest / 8);
        
        if(!check_movement(pos, dest, 'p', chessboard))
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