#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
class Coord
{
private:
    int x = 0;
    int y = 0;

public:
    Coord(int x, int y);

    int getX() const;
    int getY() const;
};

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

#endif