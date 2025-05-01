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

class Grille {
    private:
        vector<vector<int>> cases;
    
    public:
        Grille();
        bool caseVide(Coord c) const;
        int getCase(Coord c) const;
        void videCase(Coord c);
        int setCase(Coord c, int id);
    
};

#endif