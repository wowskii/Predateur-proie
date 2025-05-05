tests: test.o coord.o animal.o population.o grille.o jeu.o
	g++ -o tests test.o coord.o animal.o population.o grille.o jeu.o

main: main.o coord.o animal.o population.o grille.o jeu.o graphique.o
	g++ -o main main.o coord.o animal.o population.o grille.o jeu.o graphique.o -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm *.o
	rm tests