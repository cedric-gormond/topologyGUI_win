//
// Created by Cedric Gormond on 06/02/2019.
//

#ifndef TOPOLOGYGUI_SURFACE_H
#define TOPOLOGYGUI_SURFACE_H

#include "ctr.hpp"
#include "gen_tools.h"
#include <cmath>

/*
 * getSurfaceHexa : returns surface of a 2D hexagonal topology
 */
int getSurfaceHexa(constraint *ctr, int diagonal, int size);

/*
 * getSurface2D : returns surface of a 2D topology
 */
int getSurface2D(constraint *ctr, int diagonale, int size);

/*
 * getSurface3D : returns surface of a 3D topology
 */
int getSurface3D(constraint *ctr, int d, int size);

/*
 * getDfromS2D : get distance2D from the surface of a mesh2D
 */
int getDfromS2D(int gens[3], int coord[4], int surface_2D);

/*
 * getDfromSHexa : get diagonal from the surface of a hexa
 */
int getDfromSHexa(int gens[3], int coord[4], int surface_hexa);

/*
 * getDfromS3D : get distance3D from the surface of a mesh3D
 */
int getDfromS3D(int gens[3], int coord[4], int surface_3D);

#endif //TOPOLOGYGUI_SURFACE_H
