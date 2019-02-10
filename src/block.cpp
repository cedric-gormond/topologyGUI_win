//
// Created by Cedric Gormond on 25/01/2019.
//

#include "block.h"
#include "ctr.hpp"


Block::Block() :
        position(sf::Vector2f()),
        width(40.0f),
        height(20.0f),
        colour(sf::Color())
{
}

Block::Block(float X0, float Y0, int Width, int Height) :
        //width(40.0f),
        // height(20.0f)
        width(Width),
        height(Height)
{
    position.x = X0;
    position.y = Y0;

    colour = sf::Color::Transparent;

    block.setSize(sf::Vector2f(width, height));
    block.setFillColor(colour);
    block.setPosition(position);
    block.setOutlineThickness(2);
    block.setOutlineColor(sf::Color(150, 50, 250));
}

Block::~Block() {
}

void Block::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(block);
}
