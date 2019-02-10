//
// Created by Cedric Gormond on 25/01/2019.
//

#include "lineContainer.h"
#include "ctr.hpp"
#include "gen_tools.h"

ContainerOfLines::ContainerOfLines() {
}

ContainerOfLines::ContainerOfLines(int size, const sf::Vector2f pos, constraint *ctr, int distance) {

    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    for (int k = 0; k < (size - gen_max[0] - 1); ++k) {
        blockContainer.push_back(Line(ctr[k].CenterX - 1, ctr[k].CenterY - 1, ctr[k].width, ctr[k].heigth, distance, 2)); //-1 p
        blockContainer.push_back(Line(ctr[k].CenterX - 1, ctr[k].CenterY - 1, ctr[k].width, ctr[k].heigth, 2, distance)); //-1 p            pbloc++;
    }

    for (int k = 0; k < (size - gen_max[1] - 1); ++k) {
        blockContainer.push_back(Line(ctr[k].CenterX - 1, ctr[k].CenterY - 1, ctr[k].width, ctr[k].heigth, distance, 2)); //-1 p
        blockContainer.push_back(Line(ctr[k].CenterX - 1, ctr[k].CenterY - 1, ctr[k].width, ctr[k].heigth, 2, distance)); //-1 p            pbloc++;
    }

    /*
    int i, j, pbloc;

    i = 0;
    pbloc = 0;
    while (i<=max_Y) {
        j=0;
        while (j<=max_X) {
            //blockContainer.push_back(Line(ctr[pbloc].CenterX - 1, ctr[pbloc].CenterY - 1, ctr[pbloc].width, ctr[pbloc].heigth, distance, 2)); //-1 p
            //blockContainer.push_back(Line(ctr[pbloc].CenterX - 1, ctr[pbloc].CenterY - 1, ctr[pbloc].width, ctr[pbloc].heigth, 2, distance)); //-1 p            pbloc++;
            pbloc++;
            j++;
        }
        //blockContainer.push_back(Line(ctr[pbloc].CenterX - 1, ctr[pbloc].CenterY - 1, ctr[pbloc].width, ctr[pbloc].heigth, 2, distance)); //-1 p
        i++;
    }
     */
}

ContainerOfLines::~ContainerOfLines() {
}

std::vector<Line> &ContainerOfLines::getContainer() {
    return blockContainer;
}

void ContainerOfLines::drawContainer(sf::RenderWindow &window) {
    for (std::size_t i = 0; i < blockContainer.size(); ++i) {
        window.draw(blockContainer[i]);
    }
}

void ContainerOfLines::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    for (std::size_t i = 0; i < blockContainer.size(); ++i) {
        renderTarget.draw(blockContainer[i]);
    }
}