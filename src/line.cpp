//
// Created by Cedric Gormond on 25/01/2019.
//

#include "line.h"

Line::Line() :
        position(sf::Vector2f()),
        width(10.0f),
        height(2.0f),
        colour(sf::Color())
{
}

Line::Line(float Xc, float Yc, int Width, int Height, int distanceW, int distanceH) :
        width(distanceW),
        height(distanceH)
{
    position.x = Xc;
    position.y = Yc;

    colour = sf::Color::Red;

    block.setSize(sf::Vector2f(width, height));
    block.setFillColor(colour);
    block.setPosition(position);
    //block.setOutlineThickness(2);
    //block.setOutlineColor(sf::Color(255,165,0));
}

Line::~Line() {
}

void Line::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(block);
}
