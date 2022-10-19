// https://linuxhint.com/unicode-c/

# include <stdio.h>
# include <string.h>
# include <wchar.h>

// Linux library
#include <locale.h>

// Windows Libraries
#include <fcntl.h>
# include <io.h>

//Permet d'afficher le cadre supérieur de l'échéquier
void interface_topedge () {
    wprintf(L"\x2554");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2550\x2550\x2564");
    }
    wprintf(L"\x2550\x2550\x2557 \n");
}

//Permet d'afficher le cadre inférieur de l'échéquier
void interface_botedge () {
    wprintf(L"\x255A");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2550\x2550\x2567");
    }
    wprintf(L"\x2550\x2550\x255D \n");
    wprintf(L" A  B  C  D  E  F  G  H");
}

//Permet d'afficher les cadres intermédiaires de l'échéquier
void interface_interedge () {
    wprintf(L"\x255F");
    for (int i = 1; i < 8 ; i++){
        wprintf(L"\x2500\x2500\x253C");
    }
    wprintf(L"\x2500\x2500\x2562 \n");
}

int main (int argc, char ** argv){
    
    // On passe la console Windows en Unicode  
    _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
    
    // On passe la console Linux en Unicode  
    setlocale(LC_CTYPE, "");

    interface_topedge();

    //wprintf(L"\x2551\x2654 \x2502\x265A \x2551 \n");
    for (int i = 1; i <8; i++){
        interface_interedge ();
    }
    interface_botedge();
    return 0;
}