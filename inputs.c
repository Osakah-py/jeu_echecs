# include "inputs.h"

// VARIABLES GLOBALES ---------------------------------------------------------------------------------
const wchar_t pieces [6][9] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

// VIDAGE DU BUFFER A CHAQUE ENTREE -------------------------------------------------------------------
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
// UTILISATEUR CHOISI PIECE A DEPLACER ----------------------------------------------------------------
int input_a_deplacer (char chessboard[][8], int color, int * y, int * x, char * piece){

    // Entrée utilisateur
    wprintf(L"Quel pièce voulez vous déplacer ? \n");
    char entree[3];
    
    fgets(entree, 3, stdin);
    viderBuffer();

    *x = (int) toupper(entree[0]) - 65;
    *y = (int) entree[1] - 1 - 48;
    
    // On vérifie que l'entrée est correcte
    int pion;
    pion = detection(*y, *x, color, chessboard, piece);
    
    // On demande ou il veut déplacer son pion si c'est juste
    if (pion == -1){
        wprintf(L"Aucune pièce à vous en %c%d \n", entree[0], entree[1]);
        return 0;
    } else {
       wprintf(L"Où voulez vous déplacer votre %s ? \n", pieces[pion]);
       return 1;
    }
}

int input_ou_deplacer(){
    char entree[3];
    
    fgets(entree, 3, stdin);
    viderBuffer();
    
    int x = (int) toupper(entree[0]) - 65; // 65 corespond au code ASCII du A
    int y = (int) entree[1] - 1 - 48; // 48 corespond au code ASCII du 0

    return x + 8 * y;

}