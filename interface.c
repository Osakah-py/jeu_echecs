// https://linuxhint.com/unicode-c/

# include "interface.h"

// UNICODE DE CHAQUE PIECE ---------------------------------------------------------------------------------
const char lettre[13] = {'R', 'D', 'T', 'F', 'C', 'P', 'r', 'd', 't', 'f', 'c', 'p', '0'};
const wchar_t unicode[13] = {0x2654, 0x2655, 0x2656, 0x2657, 0x2658, 0x2659, 0x265A, 0x265B, 0x265C, 0x265D, 0x265E, 0x265F, 0x0020};
//const wchar_t pieces [6][8] = {L"roi", L"dame", L"tour", L"fou", L"cavalier", L"pion"};
extern char chessboard[][8];

// INITIALISATION ECHEQUIER --------------------------------------------------------------------------------
void init_echequier (){
    
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
void affichage (char chessboard[][8]){
    // Affichage de l'échequier
    interface_topedge(); 

    for (int i = 0; i < 8; i++){
        
        wprintf(L"%d \x2551 %lc", i+1, unicode[indice(chessboard [i][0])]); // Affichage du premier élement (on le sépare du reste pour avoir le bord)
        
        for (int j = 1; j < 8; j++){
            wprintf(L"  \x2502 %lc", unicode[indice(chessboard [i][j])]); // on affiche chaque indice unicode des pièces
        }

        wprintf(L"  \x2551 \n"); // On ferme le cadre

        if (i != 7){ 
        interface_interedge (); // Affichage du cadriage intermédiaire, on ne le veut pas pour la dernière ligne (le cadre est déjà là)
        }
    }
    interface_botedge();
}   

int detection (int y, int x, int color, char chessboard[][8]){
    
    // Verifions si il s'agit bien d'une pièce
    if (chessboard[y][x] == '0'){
        return -1;
    }
    // Veérifion que la couleur de la pièce corespond à celle du joueur
    if ( isupper(chessboard[y][x]) && color == 1){
        return indice(chessboard[y][x]);
    } 
    else if (!isupper(chessboard[y][x]) && color == 0){
        return indice(chessboard[y][x]) - 6; // (déphasage de 6 pièces)
    }
    return -1;
}


// ZONE EN CHANTIER POUR L'INPUT
// (avec un bulldozer CAT)
// je peux aussi ramener un marteau piqueur stv
/*void zone_en_chantier()
{
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
}*/