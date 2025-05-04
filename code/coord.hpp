#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ctime>

#ifndef TAILLEGRILLE
#define TAILLEGRILLE 40
#endif

using namespace std;

class Ensemble { 
    private :
        vector<int> t;
        int card;
        static const int MAXCARD = 20000;

    public :
        Ensemble();
        bool estVide();
        int cardinal();
        void affiche(ostream &out) const;
        friend ostream& operator<<(ostream& out, const Ensemble& e);
        void ajoute(int a);
        int tire();
        std::vector<int>::const_iterator begin() const { return t.begin(); }
        std::vector<int>::const_iterator end() const { return t.end(); }
};
class Coord
{
private:
    int lig;
    int col;

public:
    Coord();
    Coord(int l, int c);
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