#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "coord.hpp"
#include "animal.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <unordered_map>

using namespace std;

class Population {
    private:
        std::unordered_map<int, Animal> map;
        int nextId = 0;
    
    public:
    Population() : map() {}
    
    Animal get(int id) const;
    Ensemble getIds() const;
    int reserve();
    void set(int id, const Animal &animal);
    void supprime(int id);
};

#endif