//
//  ctr.cpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//
#include "ctr.hpp"


// METHODS
void initConstraint(constraint *ctr){
    ctr->name   = " ";
    ctr->X_down = "0";
    ctr->Y_down = "0";
    ctr->X_up   = "0";
    ctr->Y_up   = "0";

    ctr->GenY   = "-1";
    ctr->GenY   = "-1";
    ctr->GenZ   = "-1";

    ctr->CenterX    = 0;
    ctr->CenterY    = 0;

    ctr->width      = 0;
    ctr->heigth     = 0;
}

constraint* createConstraint(int *gens, int *coord){
    int size = gens[0] * gens[1];
    auto * ctr_temp = new constraint[size];

    //COORD : X0 Y0 X1 Y1
    ctr_temp[0].X_down = std::to_string(coord[0]);
    ctr_temp[0].Y_down = std::to_string(coord[1]);
    ctr_temp[0].X_up   = std::to_string(coord[2]);
    ctr_temp[0].Y_up   = std::to_string(coord[3]);

    for (int i = 0; i < size; ++i) {
        ctr_temp[i].name    = std::to_string(i+1);
        ctr_temp[i].CenterX = (coord[0] + coord[2])/2;
        ctr_temp[i].CenterY = (coord[1] + coord[3])/2;
        ctr_temp[i].width   = (coord[2] - coord[0]);
        ctr_temp[i].heigth  = (coord[3] - coord[1]);
    }

    int bloc = 0;
    for (int j = 0; j < gens[0]; ++j) {
        for (int k = 0; k < gens[1]; ++k) {
            ctr_temp[bloc].GenX    = std::to_string(k);
            ctr_temp[bloc].GenY    = std::to_string(j);
            bloc++;
        }
    }
    return ctr_temp;
}

constraint* createConstraint3D(int *gens, int *coord){
    int size = gens[0] * gens[1] * (gens[2]+1);
    constraint* ctr_temp = new constraint[size];

    //COORD : X0 Y0 X1 Y1
    ctr_temp[0].X_down = std::to_string(coord[0]);
    ctr_temp[0].Y_down = std::to_string(coord[1]);
    ctr_temp[0].X_up   = std::to_string(coord[2]);
    ctr_temp[0].Y_up   = std::to_string(coord[3]);

    for (int i = 0; i < size; ++i) {
        ctr_temp[i].name    = std::to_string(i+1);
        ctr_temp[i].CenterX = (coord[0] + coord[2])/2;
        ctr_temp[i].CenterY = (coord[1] + coord[3])/2;
        ctr_temp[i].width   = (coord[2] - coord[0]);
        ctr_temp[i].heigth  = (coord[3] - coord[1]);
    }

    int bloc = 0;

    for (int i = 0; i < gens[2] + 1; ++i) {
        for (int j = 0; j < gens[0]; ++j) {
            for (int k = 0; k < gens[1]; ++k) {
                ctr_temp[bloc].GenZ    = std::to_string(i);
                ctr_temp[bloc].GenX    = std::to_string(k);
                ctr_temp[bloc].GenY    = std::to_string(j);
                bloc++;
            }
        }
    }

    return ctr_temp;
}