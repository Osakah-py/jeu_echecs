# include "inputs.h"

const wchar_t pieces [6][8] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

int input_a_deplacer (char chessboard[][8]){

    // Entrée utilisateur
    char y;
    int x;
    wprintf(L"Quel pièce voulez vous déplacer ? \n");
    scanf("%c %d", &y, &x);

    // On vérifie que l'entrée est correcte
    int pion;
    pion = detection(x - 1, (int) y - 65, 1, chessboard);
    
    // On demande ou il veut déplacer son pion si c'est juste
    if (pion == -1){
        wprintf(L"Aucune pièce à vous en %c%d", y, x);
        return 0;
    } else {
       wprintf(L"Où voulez vous déplacer votre %s ? \n", pieces[pion]);
       return 1;
    }
}