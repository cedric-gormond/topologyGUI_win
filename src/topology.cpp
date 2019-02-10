//
//  topology.cpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#include "topology.hpp"


void resize_dimensions(constraint *ctr ,int size, int vec2i[2]){
    for (int i=0; i<size; i++) {
        ctr[i].width    = vec2i[0];
        ctr[i].heigth   = vec2i[1];
    }
}

void dimensions_of_bloc(constraint *ctr ,int size){
    for (int i=0; i<size; i++) {
        //dimensions
        ctr[i].width    = abs(stoi(ctr[i].X_up)-stoi(ctr[i].X_down));
        ctr[i].heigth   = abs(stoi(ctr[i].Y_up)-stoi(ctr[i].Y_down));

        //center
        ctr[i].CenterX  = abs(stoi(ctr[i].X_up)+stoi(ctr[i].X_down)) / 2;
        ctr[i].CenterY  = abs(stoi(ctr[i].Y_up)+stoi(ctr[i].Y_down)) / 2;
    }
}

int distance_between_blocs(constraint *ctr, int bloc1, int bloc2)
{
    int distance = 0;
    int XC_1,XC_0,YC_1,YC_0;

    XC_0 = ctr[bloc1].CenterX;
    YC_0 = ctr[bloc1].CenterY;

    XC_1 = ctr[bloc2].CenterX;
    YC_1 = ctr[bloc2].CenterX;

    if ((bloc1 != bloc2)) {
        //distance = sqrt(pow((XC_1 - XC_0),2) + pow((YC_1 - YC_0),2)); //Euclidean space
        distance = abs(XC_1 - XC_0) + abs(YC_1 - YC_0); //Mahnattan
    }
    return distance;
}

constraint* set2D(constraint *ctr, int distance, int size)
{
    auto *ctr_resize = new constraint[size];
    //initConstraint(ctr_resize);

    ctr_resize = ctr; //copy data

    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    // recalculate every center and assumes that pblock is bottom_left
    int i, j, pbloc;

    i = j = pbloc = 0;
    while (i<=gen_max[1]) {
        j=0;
        while (j<=gen_max[0]) {
            pbloc++;
            ctr_resize[pbloc].CenterX = ctr_resize[pbloc-1].CenterX + distance;
            ctr_resize[pbloc].CenterY = ctr_resize[pbloc-1].CenterY;
            j++;
        }
        ctr_resize[pbloc].CenterX = ctr_resize[0].CenterX ;
        ctr_resize[pbloc].CenterY = ctr_resize[pbloc].CenterY + distance;
        i++;
    }

    // recalculate every X0Y0 and X1Y1
    for (int i=0; i<size; i++) {
        ctr_resize[i].X_down = std::to_string(ctr_resize[i].CenterX - (ctr_resize[i].width/2));  // X0
        ctr_resize[i].X_up   = std::to_string(ctr_resize[i].CenterX + (ctr_resize[i].width/2));  // X1
        ctr_resize[i].Y_down = std::to_string(ctr_resize[i].CenterY - (ctr_resize[i].heigth/2)); // Y0
        ctr_resize[i].Y_up   = std::to_string(ctr_resize[i].CenterY + (ctr_resize[i].heigth/2)); // Y1
    }
    return ctr_resize;
}

constraint* setHexa(constraint *ctr, int r, int size)
{
    constraint *ctr_resize = new constraint[size];

    ctr_resize = ctr; //copy

    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr_resize, size);

    // please refer to sketch
    int i, j, pbloc;
    int d = r*cos(30 * 3.14/180);
    int o = r*sin(30 * 3.14/180);

    // recalculate every center and assumes that pblock is bottom_left
    i = 0;
    j = pbloc = 0;
    while (i<=gen_max[0]) {
        j=0;
        while (j<=gen_max[1]) {
            pbloc++;
            ctr_resize[pbloc].CenterX = ctr_resize[pbloc-1].CenterX;
            ctr_resize[pbloc].CenterY = ctr_resize[pbloc-1].CenterY + d; //radius*cos(30 * 3.14/180) = distance
            j++;
        }
        i++;
        if (i%2 != 0) {
            ctr_resize[pbloc].CenterX = ctr_resize[pbloc].CenterX + d;
            ctr_resize[pbloc].CenterY = ctr_resize[0].CenterY + o;
        } else {
            ctr_resize[pbloc].CenterX = ctr_resize[pbloc].CenterX + d;
            ctr_resize[pbloc].CenterY = ctr_resize[0].CenterY;
        }
        //i++;
    }

    // recalculate every X0Y0 and X1Y1
    for (int i=0; i<size; i++) {
        ctr_resize[i].X_down = std::to_string(ctr_resize[i].CenterX - (ctr_resize[i].width/2));  // X0
        ctr_resize[i].X_up   = std::to_string(ctr_resize[i].CenterX + (ctr_resize[i].width/2));  // X1
        ctr_resize[i].Y_down = std::to_string(ctr_resize[i].CenterY - (ctr_resize[i].heigth/2)); // Y0
        ctr_resize[i].Y_up   = std::to_string(ctr_resize[i].CenterY + (ctr_resize[i].heigth/2)); // Y1
    }
    return ctr_resize;
}

constraint* set3D(constraint *ctr, int distance, int size){
    auto *ctr_resize = new constraint[size];

    ctr_resize = ctr; // copy the data from ctr into ctr_resize

    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    // recalculate every center and assumes that pblock is bottom_left
    int i, j, k, pbloc;

    ctr_resize[0].CenterX = ctr[0].CenterX;
    ctr_resize[0].CenterY = ctr[0].CenterY;

    i = j = pbloc = 0;
    k=0;
    while (k<=gen_max[2]) {
        i = 0;
        while (i<=gen_max[1]) {
            j=0;
            while (j<=gen_max[0]) {
                pbloc++;
                ctr_resize[pbloc].CenterX = ctr_resize[pbloc-1].CenterX + distance;
                ctr_resize[pbloc].CenterY = ctr_resize[pbloc-1].CenterY;
                j++;
            }
            ctr_resize[pbloc].CenterX = ctr_resize[0].CenterX + (distance/2)*k; //it works only with Z=2
            ctr_resize[pbloc].CenterY = ctr_resize[pbloc].CenterY + distance;
            i++;
        }
        ctr_resize[pbloc].CenterX = ctr_resize[0].CenterX + (distance/2);
        ctr_resize[pbloc].CenterY = ctr_resize[0].CenterY + (distance/2);
        ctr_resize[pbloc].GenZ = std::to_string(k + 1);
        k++;
    }

    // recalculate every X0Y0 and X1Y1
    for (int i=0; i<size; i++) {
        ctr_resize[i].X_down = std::to_string(ctr_resize[i].CenterX - (ctr_resize[i].width/2));  // X0
        ctr_resize[i].X_up   = std::to_string(ctr_resize[i].CenterX + (ctr_resize[i].width/2));  // X1
        ctr_resize[i].Y_down = std::to_string(ctr_resize[i].CenterY - (ctr_resize[i].heigth/2)); // Y0
        ctr_resize[i].Y_up   = std::to_string(ctr_resize[i].CenterY + (ctr_resize[i].heigth/2)); //Y1
    }

    return ctr_resize;
}

