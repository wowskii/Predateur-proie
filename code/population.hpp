#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "coord.hpp"
#include "animal.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

class Population {
    private:
    vector<Animal> t;

    public:
    Population();
    
    Animal get(int id) const;
    Ensemble getIds() const;

    // int reserve();
    // void set();
    // void supprime(int id);
};

#endif