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
#include <fstream>
#include <typeinfo>

using namespace std;

class Jeu {
    private:
    Grille g;
    Population p;

    static int MinFreeBirthLapin;
    static float ProbReproLapin;

    static int FoodInit;
    static int FoodLapin;
    static int FoodReprod;
    static int AgeReprod;
    static int MaxFood;
    static float ProbBirthRenard;

    public:
    Animal getAnimal(int id);
    Grille getGrille();
    Population getPopulation();
    Jeu(float probLapins, float probRenard);
    int ajouteAnimal(Espece e, Coord c, Sexe s);
    int mortAnimal(int id);
    void afficher() const;
    void verifieGrille() const;
    Ensemble voisinsVides(Coord c) const;
    Ensemble voisinsEspece(Coord c, Espece e) const;
    void deplacerAnimal(Animal &a);
    void testCoherence() const;
    bool peutReproduire(const Coord& c, Espece e, Sexe sexe);
    void reproduire(int id, Coord c_initial);

    pair<int,int> etape();
    bool cycleFini() const;
    void recenseData(pair<int,int> pop, int etape, ostream& fichier) const;
    void choisirParametres();
};


#endif