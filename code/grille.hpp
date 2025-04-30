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
        vector<vector<Animal>> cases;
    
    public:
        bool caseVide(int x, int y) const;
        void getCase(int x, int y) const;
        void videCase(int x, int y);
        void setCase(int x, int y, const Animal& a);
    
};

#endif