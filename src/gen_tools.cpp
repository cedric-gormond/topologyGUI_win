//
// Created by Cedric Gormond on 26/01/2019.
//

#include "gen_tools.h"

std::vector<int> maxGen(constraint *ctr, int size){

    std::vector<int> vect;

    int MAX = 0;
    for (int I = 0; I < size; I++) {
        if (stoi(ctr[I].GenX) > stoi(ctr[MAX].GenX)) {
            MAX = I;
        }
    }
    vect.push_back(stoi(ctr[MAX].GenX));

    MAX = 0;
    for (int I = 0; I < size; I++) {
        if (stoi(ctr[I].GenY) > stoi(ctr[MAX].GenY)) {
            MAX = I;
        }
    }
    vect.push_back(stoi(ctr[MAX].GenY));

    MAX = 0;
    for (int I = 0; I < size; I++) {
        if (stoi(ctr[I].GenZ) > stoi(ctr[MAX].GenZ)) {
            MAX = I;
        }
    }
    vect.push_back(stoi(ctr[MAX].GenZ));

    return vect;
}

std::string setGen(constraint *ctr, int index, int size)
{
    /*
     * GenZ doesn't matter
     */

    std::string correct_gen;
    std::string str_X, str_Y;

    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    int max_X = gen_max[0];
    int max_Y = gen_max[1];


    // Determines the first expression which depends on Y
    if(stoi(ctr[index].GenY) == 0){
        str_Y = ".GEN_ROUTER_BOTTOM";
    }

    if (stoi(ctr[index].GenY) == max_Y) {
        str_Y = ".GEN_ROUTER_TOP";
    }

    if ((stoi(ctr[index].GenY) != 0) && (stoi(ctr[index].GenY) != max_Y)) {
        str_Y = ".GEN_ROUTER_MIDDLE";
    }

    // Determines the second expression which depends on X
    if(stoi(ctr[index].GenX) == 0){
        str_X = str_Y + "_LEFT";
    }

    if (stoi(ctr[index].GenX) == max_X) {
        str_X = str_Y + "_RIGHT";
    }

    if ((stoi(ctr[index].GenX) != 0) && (stoi(ctr[index].GenX) != max_X)) {
        str_X = str_Y + "_CENTRAL";
    }

    //final gen
    correct_gen = str_Y + str_X;

    return correct_gen;
}