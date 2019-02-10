#include "blockContainer.h"

ContainerOfBlocks::ContainerOfBlocks() {
}

ContainerOfBlocks::ContainerOfBlocks(int size, const sf::Vector2f pos, constraint *ctr) {


    for (int j = 0; j < size; ++j) {
        blockContainer.push_back(Block(stoi(ctr[j].X_down), stoi(ctr[j].Y_down), ctr[j].width,ctr[j].heigth));
    }

    //float x = pos.x;
    //float y = pos.y;
    //for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i) {
    //    blockContainer.push_back(Block(x, y));
    //    x += 50.0f;
    //}
}

ContainerOfBlocks::~ContainerOfBlocks() {
}

std::vector<Block> &ContainerOfBlocks::getContainer() {
    return blockContainer;
}

void ContainerOfBlocks::drawContainer(sf::RenderWindow &window) {
    for (std::size_t i = 0; i < blockContainer.size(); ++i) {
        window.draw(blockContainer[i]);
    }
}

void ContainerOfBlocks::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    for (std::size_t i = 0; i < blockContainer.size(); ++i) {
        renderTarget.draw(blockContainer[i]);
    }
}