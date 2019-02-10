#ifndef BLOCKCONTAINER_H_INCLUDED
#define BLOCKCONTAINER_H_INCLUDED

#include "block.h"
#include "ctr.hpp"

class ContainerOfBlocks : public sf::Drawable {
public:
    ContainerOfBlocks(); //constructor
    ContainerOfBlocks(int size, const sf::Vector2f pos, constraint *ctr);
    ~ContainerOfBlocks();

    std::vector<Block> &getContainer();
    void drawContainer(sf::RenderWindow &window);

private:
    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

    std::vector<Block> blockContainer;
};

#endif