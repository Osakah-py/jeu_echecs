# Les nom des sous-dossiers du projet 
CODEDIR = ./code/game_logic .
INCDIR = headers headers/logic

# Compilation de fichiers pour construire des programmes.
# Vous pouvez rajouter des commentaires en utilisant le symbole #


# Donner ci-dessous le nom des fichiers intermédiaires à générer
# Si vous indiquez un nom de module ici, cela sous-entend que votre programme
# fait appel à des fonctions déclarées dans un fichier .h et définies dans un
# fichier .c de même nom de base que celui du fichier objet généré en .o.
# Nom de base : nom du fichier sans extension.
SCRIPTS = $(foreach D, $(CODEDIR), $(wildcard $(D)/*.c))
OBJETS = $(patsubst %.c, %.o, $(SCRIPTS))


# Donner ci-dessous le nom du fichier exécutable à produire
NOM_EXECUTABLE = main

# Ligne ci-dessous à conserver
OPTIONS = -std=c99 -Wall -Wextra -Wvla -fsanitize=address,undefined 
IOPTION = $(foreach D,$(INCDIR),-iquote$(D))
# Règle principale
all: $(NOM_EXECUTABLE)

$(NOM_EXECUTABLE): $(OBJETS)
	gcc $(OPTIONS) $(IOPTION) $^ -o $@ 

%.o : %.c
	gcc -c $(OPTIONS) $(IOPTION) $^ -o $@

clean:
	-rm -f *.o $(addsuffix /*.o, $(CODEDIR))
	-rm $(NOM_EXECUTABLE)	