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

void test();