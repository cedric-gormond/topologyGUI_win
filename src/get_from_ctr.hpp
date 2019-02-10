//
//  get_from_ctr.hpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#ifndef get_from_ctr_hpp
#define get_from_ctr_hpp

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "ctr.hpp"
#include "gen_tools.h"

/*
 * getNumberBlocsFromCtr : Get the number of pblocs (routers)
 */
int getNumberBlocsFromCtr(std::ifstream &file);

/*
 * getBlocsFromCtr : Get all the values by using regular expressions
 */
void getBlocsFromCtr(std::ifstream &file, constraint *ctr);

/*
 * getGenFromCtr : Get all the values by using regular expressions
 */
void getGenFromCtr(std::ifstream &file, constraint *ctr);

/*
 * displayBlocsFromCtr : display blocs in console
 */
void displayBlocsFromCtr(constraint *ctr, int size);

#endif /* get_from_ctr_hpp */
