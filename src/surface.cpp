//
// Created by Cedric Gormond on 06/02/2019.
//

#include "surface.h"


int getSurfaceHexa(constraint *ctr, int r, int size){
    //return pow(r,2)*cos(30);
    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    int total_width     = static_cast<int>(gen_max[0] * r * cos(30 * 3.14 / 180) + ctr[0].width);
    int total_heigth    = (gen_max[1]*r + ctr[0].heigth);
    return (total_width * total_heigth);
}

int getSurface2D(constraint *ctr, int distance, int size){
    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    int total_width     = (gen_max[0]*distance + ctr[0].width);
    int total_heigth    = (gen_max[1]*distance + ctr[0].heigth);
    return (total_width * total_heigth);
}

int getSurface3D(constraint *ctr, int d, int size){
    std::vector<int> gen_max(3);
    gen_max = maxGen(ctr, size);

    int total_width     = d*(gen_max[0] + 0.5) + ctr[0].width;
    int total_heigth    = d*(gen_max[0] + 0.5) + ctr[0].heigth;
    return (total_width * total_heigth);
}

int getDfromS2D(int gens[3], int coord[4], int S){
    int d = 0;
    int n = gens[0];
    int m = gens[0];
    int w = coord[2]-coord[0];
    int h = coord[3]-coord[1];
    int D = 0;

    // We want to resolve ((n-1)d+w)*((m-1)d+h) = S
    // which is equivalent to (n-1)(m-1)d^2 + d((n-1)h + (m-1)w) + wh-S = 0

    //Delta : D = b^2 - 4ac
    D = pow((n-1)*h+(m-1)*w,2) - 4*(n-1)*(m-1)*(w*h-S);

    //D1
    if (D > 0)  d= (-((n-1)*h+(m-1)*w) + sqrt(D))/(2*(n-1)*(m-1));

    return d;
}

/*
 * getDfromS2D :
 */
int getDfromSHexa(int gens[3], int coord[4], int S){
    int r = 0;
    int n = gens[0];
    int m = gens[0];
    int w = coord[2]-coord[0];
    int h = coord[3]-coord[1];
    int D = 0;

    // We want to resolve ((n-1)Rcos(30)+w)*((m-1)r+h) = S
    // which is equivalent to (n-1)(m-1)r^2cos(30) + r((n-1)hcos(30) + (m-1)w) + wh-S = 0

    //Delta : D = b^2 - 4ac
    D = pow((n-1)*h*cos(30 * 3.14/180)+(m-1)*w,2) - 4*(n-1)*(m-1)*(w*h-S)*cos(30 * 3.14 / 180);

    //r1
    if (D > 0)  r= (int)(-((n-1)*h*cos(30 * 3.14/180)+(m-1)*w) + sqrt(D))/(2*(n-1)*(m-1)*cos(30 * 3.14/180));

    return r;
}

int getDfromS3D(int gens[3], int coord[4], int S){
    int d = 0;
    float n = gens[0];
    float m = gens[0];
    int w = coord[2]-coord[0];
    int h = coord[3]-coord[1];
    int D = 0;

    // We want to resolve ((n-0.5)d+w)*((m-0.5)d+h) = S
    // which is equivalent to (n-0.5)(m-0.5)d^2 + d((n-0.5)h + (m-0.5)w) + wh-S = 0

    //Delta : D = b^2 - 4ac
    D = pow((n-0.5)*h+(m-0.5)*w,2) - 4*(n-0.5)*(m-0.5)*(w*h-S);

    //D1
    if (D > 0)  d= (-((n-0.5)*h+(m-0.5)*w) + sqrt(D))/(2*(n-0.5)*(m-0.5));

    return d;
}

