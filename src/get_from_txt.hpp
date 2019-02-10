//
//  get_from_txt.hpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#ifndef get_from_txt_hpp
#define get_from_txt_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "ctr.hpp"
#include "gen_tools.h"

/*
 * getNumberBlocs_from_text : Get the number of pblocs (routers)
 */
int getNumberBlocs_from_text(std::ifstream& file);

/*
 * getBlocs_from_text : Get all the values by using regular expressions
 */
void getBlocs_from_text(std::ifstream& file, constraint *ctr);

/*
 * getGen_from_text : Get all the gen by using regular expressions
 */
void getGen_from_text(std::ifstream& file, constraint *ctr);





#endif /* get_from_txt_hpp */
