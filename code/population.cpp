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

    p.set(Animal(-1, Lapin, Coord(5,15)));

    p.set(Animal(-1, Renard, Coord(5,15)));

    p.set(Animal(-1, Lapin, Coord(5,15)));
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

int Population::set(Animal animal)
{
    int id = reserve();
    if (map.find(id) != map.end())
    {
        animal.setId(id);
        map[id] = animal;
        return id;
    }
    else
    {
        throw std::invalid_argument("ID not reserved");
    }
}

TEST_CASE("get, set et reserve") {
    Population p;
    int id = p.set(Animal(-1, Renard, Coord(2,4)));

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
    p.set(Animal(-1, Lapin, Coord(5,15)));
    p.set(Animal(-1, Renard, Coord(5,15)));
    int idASupprimer = p.set(Animal(-1, Lapin, Coord(5,15)));
    p.supprime(idASupprimer);
    CHECK(p.getIds().cardinal() == 2);
}