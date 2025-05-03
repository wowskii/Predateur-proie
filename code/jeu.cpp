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
    for (int i = 0; i < TAILLEGRILLE * TAILLEGRILLE; i++) {
        int r = rand() % 100;
        Coord c(i);
    
        if (r < probLapinsPourCent) ajouteAnimal(Lapin, c);
        else if (r < probLapinsPourCent + probRenardPourCent) ajouteAnimal(Renard, c);
    }
    cout << g;
}

TEST_CASE("Test visuel Constructeur Jeu") {
    Jeu j(0.4, 0.1);
}

int Jeu::ajouteAnimal(Espece e, Coord c) {
    int id = g.setCase(c, p.set(Animal(-1, e, c)));
    return id;
}

void Jeu::verifieGrille() const {
    for (int id : p.getIds()) {
        const Animal& animal = p.get(id);
        Coord coord = animal.getCoord();
        
        if (g.getCase(coord) != id) {
            throw std::runtime_error("Erreur: Animal " + std::to_string(id) + " mal placé ");
        }
    }
}
TEST_CASE("Jeu::verifieGrille()"){
    Jeu jeu(0.0, 0.0);
    Coord c(2,3);
    int test = jeu.ajouteAnimal(Lapin, c);
    CHECK_NOTHROW(jeu.verifieGrille());
}