#ifndef interface 
#define DEF_NOMDUFICHIER

# include <stdio.h>
# include <string.h>

# include <errno.h>
# include <stdlib.h>

# include <wchar.h>
# include <fcntl.h>

// Linux library
#ifdef unix
    # include <locale.h>

// Windows Libraries
#elif _WIN32
    # include <io.h>
#endif

void affichage(char chessboard[][8]);
void init_echequier (char chessboard[][8]);
#endif