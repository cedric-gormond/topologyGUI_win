//
// Created by Cedric Gormond on 25/01/2019.
//

#ifndef TOPOLOGYGUI_LINE_H
#define TOPOLOGYGUI_LINE_H

#include <SFML/Graphics.hpp>

class Line : public sf::Drawable {
public:
    Line();
    Line(float Xc, float Yc, int Width, int Height, int distanceW, int distanceH);
    virtual ~Line();

private:
    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

    sf::RectangleShape block;
    sf::Vector2f position;
    float width;
    float height;
    sf::Color colour;
};


#endif //TOPOLOGYGUI_LINE_H
