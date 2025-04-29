#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "coord.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;


enum Espece {
    Lapin,
    Renard
};

class Animal{
    private :
        int id;
        Coord coord;
        Espece espece;
        bool estVivant;
        int energie;
    public:
        Animal();
        int getId() const;
        Coord getCoord() const;
        void setCoord(int x, int y);
        void setEspece(Espece e);
        Espece getEspece() const;
        void affiche();
        bool meurt();
        bool seReproduire(int voisinVides) const;
        void mange();
        void jeune();
        int getEnergie() const;
        bool operator==(const Coord& autre) const;
};

#endif