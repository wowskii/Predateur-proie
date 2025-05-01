#include "jeu.hpp"
#include "doctest.h"


Jeu::Jeu(float probLapins, float probRenard) {
    if (probLapins < 0 || probLapins > 1 || 
        probRenard < 0 || probRenard > 1 || 
        probLapins + probRenard > 1)
        throw invalid_argument("Les probabilités, ainsi que leur somme, doit être comprises entre 0 et 1");
    float probVide = 1 - probLapins - probRenard;
    
    int probLapinsPourCent = 100*probLapins;
    int probRenardPourCent = 100*probRenard;
    srand(time(0));
    for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++) {
        int r = rand() % 100;
        
        if (r < probLapinsPourCent) ajouteAnimal(Lapin, Coord(i));
        else if (r > probLapinsPourCent && r < probLapinsPourCent + probRenardPourCent) ajouteAnimal(Renard, Coord(i));
    }
    //cout << g;
}

TEST_CASE("Test visuel Constructeur Jeu") {
    //Jeu j(0.4, 0.1);
}

int Jeu::ajouteAnimal(Espece e, Coord c) {
    int id = g.setCase(c, p.set(Animal(-1, e, c)));
    return id;
}