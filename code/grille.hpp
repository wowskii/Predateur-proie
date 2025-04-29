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
        bool caseVide();
        void getCase();
        void videCase();
        void setCase();
    
};

#endif