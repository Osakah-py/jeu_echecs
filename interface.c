// https://linuxhint.com/unicode-c/

# include <stdio.h>
# include <string.h>
# include <wchar.h>
#include <locale.h>

int main (int argc, char ** argv){
    setlocale(LC_CTYPE, "");
    wprintf(L"\x2654 \x265A \n");
    return 0;
}