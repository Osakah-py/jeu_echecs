# include "inputs.h"

// VARIABLES GLOBALES ---------------------------------------------------------------------------------
const wchar_t pieces [6][9] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

// UTILISATEUR CHOISI PIECE A DEPLACER ----------------------------------------------------------------
int input_a_deplacer (char chessboard[][8], int color){

    // Entrée utilisateur
    char y;
    int x;
    wprintf(L"Quel pièce voulez vous déplacer ? \n");
    scanf("%c %d", &y, &x);

    // On vérifie que l'entrée est correcte
    int pion;
    pion = detection(x - 1, (int) toupper(y) - 65, color, chessboard);
    
    // On demande ou il veut déplacer son pion si c'est juste
    if (pion == -1){
        wprintf(L"Aucune pièce à vous en %c%d", y, x);
        return 0;
    } else {
        wprintf(L"pion = %d \n", pion);
       wprintf(L"Où voulez vous déplacer votre %s ? \n", pieces[pion]);
       return 1;
    }
}