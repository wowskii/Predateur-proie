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

using namespace std;

class Jeu {
    private:
    Grille g;
    Population p;

    public:
    Jeu(float probLapins, float probRenard);
    int ajouteAnimal(Espece e, Coord c);
};


#endif