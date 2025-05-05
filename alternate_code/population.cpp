#include "population.hpp"
#include "doctest.h"

Animal Population::get(int id) const
{
    auto iter = map.find(id);
    if (iter != map.end())
    {
        //cout << id << " " << iter->second.getCoord() << endl;
        //cout << iter->first << id << iter->second.getId() << endl;
        return iter->second;
    }
    //throw runtime_error("Un animal d'identifiant " + to_string(id) + " n'existe pas.");
    return Animal();
}

Ensemble Population::getIds() const
{
    Ensemble e;
    for (const auto &pair : map)
    {
        //std::cout << "ID in map: " << pair.first << std::endl;
        e.ajoute(pair.first);
    }
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
        std::cout << "Recycled ID: " << id << ", map size: " << map.size() << ", freedIds size: " << freedIds.size() << std::endl;
        return id;
    }
    while (map.find(nextId) != map.end()) {
        nextId++;
    }
    std::cout << "New ID: " << nextId << ", map size: " << map.size() << ", freedIds size: " << freedIds.size() << " bucket count : " << map.bucket_count() << std::endl;
    return nextId++;
}

int Population::set(Animal &animal)
{
    int id = reserve();
    animal.setId(id);
    map[id] = animal;
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

void Population::supprime(int id) {
    cout << map.erase(id);
    freedIds.insert(id);

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