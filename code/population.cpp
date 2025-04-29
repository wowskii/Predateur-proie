#include "population.hpp"
#include "doctest.h"


Animal Population::get(int id) const
{
    auto iter = map.find(id);
    if (iter != map.end())
    {
        return iter->second;
    }
    return Animal();
}

Ensemble Population::getIds() const
{
    Ensemble e;
    for (const auto &pair : map)
    {
        e.ajoute(pair.first);
    }
    return e;
}

int Population::reserve()
{
    while (map.find(nextId) != map.end())
    {
        nextId++;
    }
    map[nextId] = Animal();
    return nextId++;
}

void Population::set(int id, const Animal &animal)
{
    if (map.find(id) != map.end())
    {
        map[id] = animal;
    }
    else
    {
        throw std::invalid_argument("ID not reserved");
    }
}

void Population::supprime(int id)
{
    map.erase(id);
}