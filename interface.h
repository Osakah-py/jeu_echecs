#ifndef interface 
#define interface

# include <stdio.h>
# include <string.h>
# include <ctype.h>

# include <errno.h>
# include <stdlib.h>

# include <wchar.h>
# include <fcntl.h>

// Linux library
#if defined(__linux__)
    # include <locale.h>
// Windows Libraries
#elif defined(_WIN32)
    # include <io.h>
#endif

// LES COULEURS ---------------------------------------------------------------
# define _RED_() "\x1b[31m"
# define _BLUE_ ()"\x1b[34m"
# define _DEFAULT_() "\x1b[39m"

// FONCTIONS ------------------------------------------------------------------
void affichage(char chessboard[][8]);
void init_echequier (char chessboard[][8]);
int detection (int y, int x, int color, char chessboard[][8], char * piece);

#endif