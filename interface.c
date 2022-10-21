// https://linuxhint.com/unicode-c/

# include <stdio.h>
# include <string.h>

# include <errno.h>
# include <stdlib.h>

# include <wchar.h>

// Linux library
#include <locale.h>

// Windows Libraries
#include <fcntl.h>
# include <io.h>

// INITIALISATION ECHEQUIER -------------------------------------------------------------------------------------
void init_echequier (char chessboard[][8]){
    
    // Gestion d'une erreur éventuelle
    errno = 0;
    // Ouverture du fichier par défaut
    FILE * flux_entree = fopen ( "Default.txt", "r");
    if ( flux_entree == NULL ){
        printf (" Une erreur s'est produite à l'ouverture du fichier %s : %s\n", flux_entree, strerror ( errno ) ) ;
        exit(EXIT_FAILURE); }
    
    //Récupération des données 
    int caractereActuel = 1;
            for (int i = 0; i <= 8; i++ ){
                for (int j = 0; j < 8; j++){
                    caractereActuel = fgetc(flux_entree); // On lit le caractère
                    
                    if ((char) caractereActuel != '\n') {
                        chessboard [i][j] = (char) caractereActuel; // On l'assimile a sa case
                    } else {j --;}
                }
            }

    // fermeture du fichier
    fclose ( flux_entree );
}


// AFFICHAGE ECHEQUIER -------------------------------------------------------------------------------------
//Permet d'afficher le cadre supérieur de l'échéquier
void interface_topedge () {
    wprintf(L"  \x2554");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2550\x2550\x2550\x2550\x2564");
    }
    wprintf(L"\x2550\x2550\x2550\x2550\x2557 \n");
}

//Permet d'afficher le cadre inférieur de l'échéquier
void interface_botedge () {
    wprintf(L"  \x255A");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2550\x2550\x2550\x2550\x2567");
    }
    wprintf(L"\x2550\x2550\x2550\x2550\x255D \n");
    wprintf(L"    A    B    C    D    E    F    G    H \n");
}

//Permet d'afficher les cadres intermédiaires de l'échéquier
void interface_interedge () {
    wprintf(L"  \x255F");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2500\x2500\x2500\x2500\x253C");
    }
    wprintf(L"\x2500\x2500\x2500\x2500\x2562 \n");
}

// MAIN FUNCTION ------------------------------------------------------------------------------------------
int main (int argc, char ** argv){
    
    // On passe la console Windows en Unicode  
    _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
    
    // On passe la console Linux en Unicode  
    setlocale(LC_CTYPE, "");

    // Initialisation de l'échéquier
    char chessboard [8][8];
    init_echequier (chessboard);
    // Affichage de l'échequier
    interface_topedge();
    for (int i = 0; i < 8; i++){
        //wprintf(L"%d \x2551 \x2658  \x2502 \x2654  \x2502 \x2655  \x2502 \x265E  \x2502 \x265A  \x2502 \x265B  \x2502 \x265C  \x2502 \x2656  \x2551 \n", i);
        wprintf(L"%d \x2551 %c", i, chessboard [i][0]);
        for (int j = 1; j < 8; j++){
            wprintf(L"  \x2502 %c", chessboard [i][j]);
        }
        wprintf(L"  \x2551 \n");
        if (i != 7){
        interface_interedge ();
        }
    }
    interface_botedge();
    return 0;
}