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
    char entree[3]; // entre[2] = '\0'
    
    fgets(entree, 3, stdin);
    viderBuffer();
    
    int x = (int) toupper(entree[0]) - 65; // 65 correspond au code ASCII du A
    int y = (int) entree[1] - 1 - 48; // 48 correspond au code ASCII du 0

    return x + 8 * y;

}

// CONFIG
int config_input (){
    char entree[1]; 
    
    fgets(entree, 2, stdin);
    viderBuffer(); 
    if (toupper(entree[0]) == 'O'){
        return 1;
    }
    if (toupper(entree[0]) == 'N'){
        return 0;
    }
    return 1; // si l'entrée est mauvais on retourne 1 quand meme
}
