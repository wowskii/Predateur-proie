#include "population.hpp"
#include "doctest.h"

Animal Population::get(int id) const
{
    return t.at(id);
}

Ensemble Population::getIds() const
{
    Ensemble e;
    for (int i = 0; i < t.size(); i++)
    {
        //std::cout << "ID in vector: " << a.getId() << std::endl;
        if (t[i].getId() != -1) e.ajoute(i);
    }
    cout << e.cardinal() << endl;
    return e;
}

TEST_CASE("getIds")
{
    Population p;
    Animal a1(-1, Lapin, Coord(5, 15));
    Animal a2(-1, Renard, Coord(5, 17));
    Animal a3(-1, Lapin, Coord(2, 15));

    p.set(a1);

    p.set(a2);

    p.set(a3);
    CHECK(p.getIds().cardinal() == 3);
    // cout << p.getIds() << endl;
}

int Population::reserve() {
    if (!freedIds.empty()) {
        int id = *freedIds.begin();
        freedIds.erase(freedIds.begin());
        if (id < t.size()) return id; 
    }
    return t.size();
}

int Population::set(Animal &animal)
{
    int id = reserve();
    animal.setId(id);
    if (id == t.size()) t.push_back(animal);
    else {t[id] = animal; cout << "recycled";}
    return id;
}

TEST_CASE("get, set et reserve")
{
    Population p;
    Animal a(-1, Renard, Coord(2, 4));
    int id = p.set(a);

    CHECK(p.get(id).getId() == id);
    CHECK(p.get(id).getEspece() == Espece::Renard);
    CHECK(p.get(id).getCoord() == Coord(2, 4));
}

void Population::updateAnimal(int id, Animal a) {
    t[id] = a;
}

void Population::supprime(int id) {
    t[id] = Animal();
    freedIds.insert(id);
    // for (auto freeid: freedIds) {
    //     cout << freeid << ",";
    // }
    // cout << endl;
}

TEST_CASE("supprime")
{
    Population p;
    Animal a1(-1, Lapin, Coord(5, 15));
    Animal a2(-1, Renard, Coord(5, 15));
    p.set(a1);
    p.set(a2);
    int idASupprimer = a1.getId();
    p.supprime(idASupprimer);
    CHECK(p.getIds().cardinal() == 1);
}