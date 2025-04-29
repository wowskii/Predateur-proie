#include "population.hpp"
#include "doctest.h"

Population::Population() {
    vector<Animal> t = {};
}

Animal Population::get(int id) const {
    for (int i = 0; i < t.size(); i++) {
        if (t[i].getId() == id) return t[i];
    }
    return Animal();
}


Ensemble Population::getIds() const {
    Ensemble e;
    for (auto a : t) {
        e.ajoute(a.getId());
    }
    return e;
}


// TEST_CASE("getIds") {
//     Population p();
// }


// int Population::reserve() {
//     Ensemble ids = this->getIds();
//     int card = ids.cardinal();
//     int id;
//     for (int i = 0; i < card; i++) {
//         for (int j = 0; j < card; j++) {
//             if (i != ids[j]) {
//                 id = i;
//                 t.push_back(Animal());
//                 return id;
//             }
//         }
//     }
// }