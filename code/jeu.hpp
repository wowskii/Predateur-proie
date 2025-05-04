#ifndef JEU_HPP
#define JEU_HPP

#include "coord.hpp"
#include "animal.hpp"
#include "population.hpp"
#include "grille.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

class Jeu {
    private:
    Grille g;
    Population p;

    public:
    Animal getAnimal(int id);
    Jeu(float probLapins, float probRenard);
    int ajouteAnimal(Espece e, Coord c);
    void afficher() const;
    void verifieGrille() const;
    Ensemble voisinsVides(Coord c) const;
    Ensemble voisinsEspece(Coord c, Espece e) const;
    void deplacerAnimal(Animal &a);
    void testCoherence() const;
};


#endif