#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "coord.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

using namespace std;

enum Sexe {
    M,
    F
};

enum Espece {
    Lapin,
    Renard
};

class Animal{
    private :
        int id;
        Espece espece;
        Sexe sexe;
        Coord coord;
        bool estVivant = true;
        int energie = 0;
        int age = 0;
        static const int LAPIN_MAX_AGE = 50;  
        static const int RENARD_MAX_AGE = 100;
    public:
        Animal();
        Animal(int id, Espece e, Coord c, Sexe s, bool vivant = true, int energy = 0) : id(id), espece(e), sexe((rand() % 2 == 0) ? M : F), coord(c), estVivant(vivant), energie(energy) {};
        int getId() const;
        void setId(int newid);
        Coord getCoord() const;
        void setCoord(Coord c);
        void setEspece(Espece e);
        Espece getEspece() const;
        void affiche();
        bool meurt();
        bool seReproduire(int voisinVides) const;
        void mange();
        void jeune();
        int getEnergie() const;
        void setEnergie(int e);
        bool isVivant() const;
        void vieillir();
        bool esttropVieux() const;
        int getAge() const;
};

#endif