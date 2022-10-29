# include "inputs.h"

// VARIABLES GLOBALES ---------------------------------------------------------------------------------
// const wchar_t pieces [6][9] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

// VIDAGE DU BUFFER A CHAQUE ENTREE -------------------------------------------------------------------
void viderBuffer() {
    int c = 0; // c pour corbeille :p
    
    while (c != '\n' && c != EOF) 
    {
        // la variable c prend le premier caractère du buffer jusqu'à arriver à la fin
        c = getchar(); 
    }
}
// RECUPERATION DES COORDONNEES UTILISATEURS ----------------------------------------------------------
int input(){
    char entree[3]; // entre[2] = '\0'
    
    fgets(entree, 3, stdin); // equivalent de scanf en un peu mieux...
    viderBuffer(); // On nettoie ce qui nous intéresse pas
    
    int x = (int) toupper(entree[0]) - 65; // 65 correspond au code ASCII du A
    int y = (int) entree[1] - 1 - 48; // 48 correspond au code ASCII du 0

    if (0 <= x  && x < 8 && 0 <= y && y < 8){
        return x + 8 * y;
    } else {
        wprintf (L"!! Entree Invalide !! Réessayez : \n");
        input(); //Si les coordonnées ne sont pas valides on redemande une entrée à l'utilisateur
    }

}

// CONFIG PREFERENCES --------------------------------------------------------------------------------
int config_input (){
    char entree[1]; // entre[1] = '\0'
    
    fgets(entree, 2, stdin);
    viderBuffer(); 
    // O = oui et N = Non
    if (toupper(entree[0]) == 'O'){
        return 1;
    }
    if (toupper(entree[0]) == 'N'){
        return 0;
    }
    return 1; // si l'entrée est mauvais on retourne 1 quand meme
}
