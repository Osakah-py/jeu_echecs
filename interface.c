// https://linuxhint.com/unicode-c/

# include "interface.h"

// UNICODE DE CHAQUE PIECE ---------------------------------------------------------------------------------
const char lettre[13] = {'R', 'D', 'T', 'F', 'C', 'P', 'r', 'd', 't', 'f', 'c', 'p', '0'};
const wchar_t unicode[13] = {0x2654, 0x2655, 0x2656, 0x2657, 0x2658, 0x2659, 0x265A, 0x265B, 0x265C, 0x265D, 0x265E, 0x265F, 0x0020};
const wchar_t pieces [6][9] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};

// INITIALISATION ECHEQUIER --------------------------------------------------------------------------------
void init_echequier (char chessboard[][8]){
    
    // Gestion d'une erreur éventuelle
    errno = 0;
    // Ouverture du fichier par défaut
    const char *nom_fichier = "Default.txt";
    FILE* flux_entree = fopen ( nom_fichier, "r");
    if ( flux_entree == NULL ){
        wprintf (L" Une erreur s'est produite à l'ouverture du fichier %s : %s\n", nom_fichier, strerror ( errno ) ) ;
        exit(EXIT_FAILURE); }
    
    //Récupération des données 
    int caractereActuel = 1;
            for (int i = 0; i < 8; i++ ){
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

// FONCTION ANNEXES AFFICHAGE ECHEQUIER -------------------------------------------------------------------------------------
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

// TROUVER L'INDICE D'UN ELEMENT (POUR L'ASSIMILER A SON UNICODE) -----------------------------------------
int indice (char let){
    int ind = -1;
    for (int i = 0; i < 13; i++){
        if (lettre[i] == let){
            ind = i;
            continue;
        }
    }
    return ind;
}

// FONCTION PRINCIPAL AFFICHAGE ECHEQUIER ------------------------------------------------------------------------------------------
void affichage (char chessboard[][8], int highlight){
    // Affichage de l'échequier
    interface_topedge(); 

    for (int i = 0; i < 8; i++){
        
        // Affichage du premier élement (on le sépare du reste pour avoir le bord)
        wprintf(L"%d \x2551 ", i+1); // Ce bord la :p
        
        if (i * 8 == highlight){
                wprintf (_BLUE_()); // si c la pièce à highlight on la met en bleu
            }

        wprintf(L"%lc"_DEFAULT_(), unicode[indice(chessboard [i][0])]); 

        for (int j = 1; j < 8; j++){
            
            wprintf(L"  \x2502 "); // On affiche le bord

            if (i * 8 + j == highlight){
                wprintf (_BLUE_()); // si c la pièce à highlight on la met en bleu
            }

            wprintf(L"%lc" _DEFAULT_(), unicode[indice(chessboard [i][j])]); // on affiche chaque indice unicode des pièces
        }

        wprintf(L"  \x2551 \n"); // On ferme le cadre

        if (i != 7){ 
        interface_interedge (); // Affichage du cadriage intermédiaire, on ne le veut pas pour la dernière ligne (le cadre est déjà là)
        }
    }
    interface_botedge();
}   

void clear() { // permet de renvoyer en haut la console a chaque tour
    #if defined(_WIN32)
        system("cls");
      
    #elif defined(__linux__)
        system("clear");   
    #endif
}

int detection (int y, int x, int color, char chessboard[][8], char * piece){
    
    // Documentation détailée de cette fonction : https://bit.ly/3sqhpW6

    // Verifions si il s'agit bien d'une pièce
    if (chessboard[y][x] != '0') {
    
        // Veérifions que la couleur de la pièce corespond à celle du joueur
        if ( isupper(chessboard[y][x]) && color == 1){
            *piece = chessboard[y][x];
            wprintf(L"Où voulez vous déplacer votre %s ? \n", pieces[indice(chessboard[y][x])]);
            return 1;
        } 
        else if (!isupper(chessboard[y][x]) && color == 0){
            *piece = chessboard[y][x];
            wprintf(L"Où voulez vous déplacer votre %s ? \n", pieces[indice(chessboard[y][x]) - 6]); // (déphasage de 6 pièces)
            return 1; 
        }
    }
    wprintf(_RED_() L"Aucune pièce à vous en %c%d \nRéessayez : \n" _DEFAULT_(), x + 65, y + 1);
    return 0;
}