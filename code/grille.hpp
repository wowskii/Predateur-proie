#ifndef GRILLE_HPP
#define GRILLE_HPP

#include "coord.hpp"
#include "animal.hpp"
#include "population.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

const int LARGEUR = 10;
const int LONGUEUR = 10;

class Grille {
    private:
        vector<vector<int>> cases;
    
    public:
        Grille();
        bool caseVide(Coord c) const;
        int getCase(Coord c) const;
        void videCase(Coord c);
        void setCase(Coord c, const Animal& a);
    
};

#endif