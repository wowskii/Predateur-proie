#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "coord.hpp"
#include "animal.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <set>

using namespace std;

class Population {
    private:
        vector<Animal> t;
        unsigned int nextId = 0;
        std::set<int> freedIds;
    public:
    Population() : t() {}
    
    Animal get(int id) const;
    Ensemble getIds() const;
    int reserve();
    int set(Animal& animal);
    void updateAnimal(int id, Animal a);
    void supprime(int id);
};

#endif