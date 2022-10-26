    # include "code/game_logic/data.h"
# include "interface.h"
# include "inputs.h"
# include "code/game_logic/movements.h"
# include "code/game_logic/check.h"


/* note : 
'0' --> case vide
'lowercase' --> piece noire
'uppercase' --> piece blanche
'p' --> pion
't' --> tour
'c' --> cavalier
'f' --> fou
'r' --> roi
'd' --> dame
*/


// VARIABLES GLOBALES -------------------------------------------------------------------------------------


// FONCTIONS SECONDAIRES ----------------------------------------------------------------------------------
int easy_check (int king_color, char chessboard[][8]);

// MAIN FONCTION ------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{ 
    
    // INTITIALISATION DES CONSOLES
    #if defined(_WIN32)
        // On passe la console Windows en Unicode 
        _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
      
    #elif defined(__linux__)
        // On passe la console Linux en Unicode
        setlocale(LC_CTYPE, "");    
    #endif
    
    char chessboard[8][8];
        
    // Initialisation de l'échéquier et des pieces 
    init_echequier(chessboard);

    int trait = 1; // trait au blanc

    //Affichage de l'échequier une première fois
    affichage(chessboard, -1); // -1 car on ne veut rien en bleu

    // Boucle principale
    while(1){
        if (trait % 2 == 1){
            wprintf(L"---- Trait au blanc ---- \n");
        } else {
            wprintf(L"---- Trait au noir ---- \n");
        }
        // Entrée utilisateur
        wprintf(L"Quel pièce voulez vous déplacer ? \n");
        int coordonees_init = input();
        // On vérifie que l'entrée est correcte
        char piece;
        int verif;
        verif = detection(coordonees_init / 8, coordonees_init % 8, trait % 2, chessboard, &piece);

        if (verif){ // la coordonnee est dans le tableau
            int dest = input();
        
            if(!check_movement(coordonees_init, dest, piece, chessboard))
            {
                wprintf(_RED_() L"Impossible de déplacer votre pièce ici ! \nRéessayez : \n" _DEFAULT_());
            } else {
                
                // on met a jour le mouvement sur l'échiquier
                update_move_chessboard(coordonees_init, dest, chessboard); 
                clear(); // On reset l'affichage
                affichage(chessboard, dest); // On affiche l'échéquier
                
                if(check_king((trait+1) % 2)) // le roi adverse est en echec ?
                
                // if (easy_check ((trait + 1) % 2, chessboard))
                {
                    wprintf(_RED_() L"--- LE ROI EST EN ECHEC ---\n" _DEFAULT_());
                }
                
                trait ++; // On passe au tour suivant
            }
        } 
    }
    return 0;
}



int easy_check (int king_color, char chessboard[][8]){
    
    // On trouve la position du roi
    int king_pos = -1;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (chessboard[i][j] == 'R' && king_color == 1){
                king_pos = j + i * 8;
                break;
            } 
            if (chessboard[i][j] == 'r' && king_color == 0){
                king_pos = j + i * 8;
                break;
            }
        }
        if (king_pos >= 0) {
            break;
        }
    }

    // On verifie si les pièces de l'échéquier peuvent atteindre cette position
    
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if(chessboard[i][j] != '0' && check_movement(j + i * 8, king_pos, chessboard[i][j], chessboard)){
                return 1;
            }
        }
    }
    return 0;
}