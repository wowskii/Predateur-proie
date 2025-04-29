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
        Animal animal;
    
    public:
        bool caseVide();
        void getCase();
        void videCase();
        void setCase();
    
};

#endif