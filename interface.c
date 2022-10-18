// https://linuxhint.com/unicode-c/

# include <stdio.h>
# include <string.h>
# include <wchar.h>

// Linux library
#include <locale.h>

// Windows Libraries
#include <fcntl.h>
# include <io.h>

int main (int argc, char ** argv){
    
    // On passe la console Windows en Unicode  
    _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
    
    // On passe la console Linux en Unicode  
    setlocale(LC_CTYPE, "");
    wprintf(L"\x2554\x2550\x2550\x2564\x2550\x2550\x2557 \n");
    wprintf(L"\x2551\x2654 \x2502\x265A \x2551 \n");
    wprintf(L"\x255A\x2550\x2550\x2567\x2550\x2550\x255D");
    return 0;
}