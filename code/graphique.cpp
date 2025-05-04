#include "graphique.hpp"

using namespace std;
using namespace sf;

void SFMLdessine(Grille g, Population p, RenderWindow &w)
{
    // ordonnee
    for (int i = 0; i < TAILLEGRILLE; i++)
    {
        // abscisse
        for (int j = 0; j < TAILLEGRILLE; j++)
        {
            int pos_x = (26 + 20 * j);
            int pos_y = (26 + 20 * i);

            // int pos_x_text = pos_x + 20;
            // int pos_y_text = pos_y + 10;

            RectangleShape tuile(Vector2f(19.f, 19.f));
            tuile.setPosition(pos_x, pos_y);

            if (g.getCase(Coord(i, j)) != -1)
            {
                switch (p.get(g.getCase(Coord(i, j))).getEspece())
                {
                case (Espece::Lapin):
                    tuile.setFillColor(Color::Yellow);
                    break;
                case (Espece::Renard):
                    tuile.setFillColor(Color::Red);
                    break;
                }
            }
            else
                tuile.setFillColor(Color::White);

            w.draw(tuile);
        }
    }
    w.display();
}