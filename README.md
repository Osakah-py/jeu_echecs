# jeu_echecs
Un jeu d'échecs en C

# Plusieurs programmes
###### main 

- prendre la requete de l'utilisateur

- l'utilsateur la case de la piece qu'il veut bouger puis la ou il veut la mettre
- renvoit une erreur si la pièce ne peut pas se deplacer 
( - confirmation ?)

###### Pieces + mouvements
- definir mouvement de chaque piece
- voir si mouvement possible

###### Interface graphique
- Afficher echequier avec chaque piece a sa place actuelle
- tableaux contenant les pieces et leurs positions
  - tableau de 8 tableaux contenant chacun 8 element de 1 a 8
###### Inputs
- Gère les entrées utilisateur


# Premiers rendus graphique
###### Test affichage à partir de la table de tables 
![rendu 3](https://jreaigle.pythonanywhere.com/static/images/rendu3.PNG "Troisieme Rendu")
###### Choix design 
![rendu 1](https://jreaigle.pythonanywhere.com/static/images/rendu1.PNG "Premier Rendu")
###### Test echequier complet
![rendu 2](https://jreaigle.pythonanywhere.com/static/images/rendu2.PNG "Deuxieme Rendu")

# Un petit coup d'oeil sur la conception du code movement
###### définition d'une pièce d'échec
une pièce est définie par :
- sa signature (ex: un pion noir a une signature "p", au contraire un pion blanc aura "P")
- son mouvement brute à valeur positive en un couple de deux entiers (x pour l'abscisse et y pour l'ordonnée)
(par exemple : un cavalier aura (2, 1) comme mouvement)
NB : un pion qui peut aller dans n'importe quelle direction aura un mouvement (0, 0)
- sa répétition et son sens (le mouvement du roi n'a pas de répétition mais il est tout de même multi-directionnel)
