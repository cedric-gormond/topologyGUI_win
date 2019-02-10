//
//  create_output_file.hpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#ifndef create_output_file_hpp
#define create_output_file_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "ctr.hpp"

/*
 * Create constraint text
 */
void create_ctr_file(std::ofstream& file_output, std::string path,constraint *ctr, int size);

/*
 * Create simplified text
 */
void create_txt_file(std::ofstream& file_output, std::string path,constraint *ctr, int size);

#endif /* create_output_file_hpp */
