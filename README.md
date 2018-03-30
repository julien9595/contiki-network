# Introducton

Un mote représente un capteur de température ou une led. Un dossier est dédié pour chaque mote.

Les leds affichent des couleurs en fonction de la température relevée :
- bleu si t <= 10
- rouge si t > 30
- vert sinon

Le capteur de température intérieur (capteur_tempIn) envoi des string d'un caractère (exemple : "R", "G", "B") et la capteur de température extérieur (capteur_tempOut) envoi des string de deux caractères (exemple : "RR", "GG, "BB"). 

Ainsi chaque mote peut savoir si le paquet est pour lui ou si il doit le broadcast à ses voisins.

# Lancement

Chaque dossier contient un makefile : 
- Target z1 ou sky pour générer des z1 ou sky motes, on utilse dans ce projet des z1 motes
- "make clean && make [mote_name].upload" pour générer le .z1 ou .sky et upload les modifications sur contiki ou alors a l'aide du bouton "reload" si une simulation est lancée

1) Create new simulation
2) Create mote -> new z1 ou sky mote en fonction de votre choix
3) Selectionner le .c dans le dossier du capteur choisi
4) Appuyez sur "compile" puis "create"
5) Pour voir l'envoi de messages entre les motes il faut activer le "radio trafic", il faut "motes environment" pour voir la range des motes
6) Appuyez sur "start" pour lancer la simulation
7) Enjoy :)
