# include "inputs.h"

// VARIABLES GLOBALES ---------------------------------------------------------------------------------
// const wchar_t pieces [6][9] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

// VIDAGE DU BUFFER A CHAQUE ENTREE -------------------------------------------------------------------
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
// RECUPERATION DES COORDONNEES UTILISATEURS ----------------------------------------------------------
int input(){
    char entree[3];
    
    fgets(entree, 3, stdin);
    viderBuffer();
    
    int x = (int) toupper(entree[0]) - 65; // 65 corespond au code ASCII du A
    int y = (int) entree[1] - 1 - 48; // 48 corespond au code ASCII du 0

    return x + 8 * y;

}
