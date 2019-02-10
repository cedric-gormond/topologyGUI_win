//
//  ctr.hpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#ifndef ctr_hpp
#define ctr_hpp

#include <iostream>
#include <string>


// STRUCT
typedef struct {
    std::string name    = " ";
    std::string X_up    = "0";
    std::string Y_up    = "0";
    std::string X_down  = "0";
    std::string Y_down  = "0";

    std::string GenX    = "-1";
    std::string GenY    = "-1";
    std::string GenZ    = "-1";
    
    int CenterX = 0;
    int CenterY = 0;

    int width   = 0;
    int heigth  = 0;
}constraint;

/*
 * initConstraint : Initialisation of constraint pointer
 */
void initConstraint(constraint *ctr);

/*
* createConstraint : Creation of minimal values
*/
constraint* createConstraint(int *gens, int *coord); // X0 Y0 X1 Y1

/*
 * createConstraint : Creation of minimal values
 */
constraint* createConstraint3D(int *gens, int *coord); // X0 Y0 X1 Y1

#endif /* ctr_hpp */
