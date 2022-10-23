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

// FONCTIONS SECONDAIRES ----------------------------------------------------------------------------------


// MAIN FONCTION ------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{ 
    #if defined(_WIN32)
        // On passe la console Windows en Unicode 
        _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
      
    #elif defined(unix) || defined(__unix__) || defined(__unix)
        // On passe la console Linux en Unicode
        printf("unicode in linux console here !\n");
        setlocale(LC_CTYPE, "");
    #endif
        
    // Initialisation de l'échéquier
    char chessboard[8][8];
    init_echequier (chessboard);

    //Affichage de l'échequier
    affichage(chessboard);
    
    // Entrée utilisateur
    char y;
    int x;
    wprintf(L"Quel pièce voulez vous déplacer ? \n");
    scanf("%c %d", &y, &x);

    // On vérifie que l'entrée est correcte
    int pion;
    pion = detection (x - 1, (int) y - 65, 1, chessboard);
    
    // On demande ou il veut déplacer son pion si c'est juste
    if (pion == -1){
        wprintf(L"Vous ne pouver rien déplacer ici");
    } else {
       wprintf(L"Où voulez vous déplacer votre %s ?", pieces[pion]);
       // Inserer le code de mouvement 
    }
    return 0;
}
