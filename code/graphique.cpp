#include "graphique.hpp"

using namespace std;
using namespace sf;

void SFMLdessine(Grille g, Population p, RenderWindow &w)
{
    Texture lapinTexture, renardTexture;
    if (!lapinTexture.loadFromFile("resources/lapin.png"))
    {
        cerr << "Error loading lapin.png" << endl;
        return;
    }
    if (!renardTexture.loadFromFile("resources/renard.png"))
    {
        cerr << "Error loading renard.png" << endl;
        return;
    }

    for (int i = 0; i < TAILLEGRILLE; i++)
    {
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
                Sprite sprite;
                switch (p.get(g.getCase(Coord(i, j))).getEspece())
                {
                case (Espece::Lapin):
                    sprite.setTexture(lapinTexture);
                    break;
                case (Espece::Renard):
                    sprite.setTexture(renardTexture);
                    break;
                }
                sprite.setPosition(pos_x, pos_y);
                w.draw(sprite);
            }
            else
            {
                // Draw a white rectangle for empty tiles
                RectangleShape tuile(Vector2f(19.f, 19.f));
                tuile.setPosition(pos_x, pos_y);
                tuile.setFillColor(Color::Green);
                w.draw(tuile);
            }
        }
    }
    w.display();
}
