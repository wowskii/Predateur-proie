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

TEST_CASE("getIds") {
    Population p;
    int id;
    id = p.reserve();
    p.set(id, Animal(id, Lapin, Coord(5,15)));
    id = p.reserve();
    p.set(id, Animal(id, Renard, Coord(5,15)));
    id = p.reserve();
    p.set(id, Animal(id, Lapin, Coord(5,15)));
    CHECK(p.getIds().cardinal() == 3);
    //cout << p.getIds() << endl;
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

TEST_CASE("get, set et reserve") {
    Population p;
    int id = p.reserve();
    p.set(id, Animal(id, Renard, Coord(2,4)));

    CHECK(p.get(id).getId() == id);
    CHECK(p.get(id).getEspece() == Espece::Renard);
    CHECK(p.get(id).getCoord() == Coord(2,4));
}

void Population::supprime(int id)
{
    map.erase(id);
}

TEST_CASE("supprime") {
    Population p;
    int id;
    id = p.reserve();
    p.set(id, Animal(id, Lapin, Coord(5,15)));
    id = p.reserve();
    p.set(id, Animal(id, Renard, Coord(5,15)));
    id = p.reserve();
    p.set(id, Animal(id, Lapin, Coord(5,15)));
    p.supprime(id);
    CHECK(p.getIds().cardinal() == 2);
}