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
#include <chrono>
#include <thread>

using namespace std;

class Jeu {
    private:
    Grille g;
    Population p;

    static const int MinFreeBirthLapin;
    static const float ProbReproLapin;

    static const int FoodInit;
    static const int FoodLapin;
    static const int FoodReprod;
    static const int MaxFood;
    static const float ProbBirthRenard;

    public:
    Animal getAnimal(int id);
    Grille getGrille();
    Population getPopulation();
    Jeu(float probLapins, float probRenard);
    int ajouteAnimal(Espece e, Coord c);
    int mortAnimal(int id);
    void afficher() const;
    void verifieGrille() const;
    Ensemble voisinsVides(Coord c) const;
    Ensemble voisinsEspece(Coord c, Espece e) const;
    void deplacerAnimal(Animal &a);
    void testCoherence() const;

    void etape();
    bool cycleFini() const;
};


#endif