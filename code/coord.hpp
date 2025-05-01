#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ctime>

using namespace std;

const int TAILLEGRILLE = 40;
class Ensemble { 
    private :
        vector<int> t;
        int card;
        static const int MAXCARD = 100;

    public :
        Ensemble();
        bool estVide();
        int cardinal();
        void affiche(ostream &out) const;
        friend ostream& operator<<(ostream& out, const Ensemble& e);
        void ajoute(int a);
        int tire();
};
class Coord
{
private:
    int lig;
    int col;

public:
    Coord();
    Coord(int lig, int col);
    Coord(int n);

    int getLig() const;
    int getCol() const;
    Ensemble voisine() const;
    int toInt() const;

    friend ostream &operator<<(ostream &out, const Coord &c);
    friend bool operator==(const Coord &c1, const Coord &c2);
    friend bool operator!=(const Coord &c1, const Coord &c2);
};


#endif