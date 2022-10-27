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
# define _YELLOW_() L"\x1b[33m"
# define _DEFAULT_() "\x1b[39m"
# define _BOLD_() "\x1b[1m"
# define _RESET_() "\x1b[0m"
// FONCTIONS ------------------------------------------------------------------
void affichage(char chessboard[][8], int highlight, int trait);
void clear();
void init_echequier (char chessboard[][8]);
int detection (int y, int x, int color, char chessboard[][8]);

#endif