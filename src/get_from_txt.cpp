//
//  get_from_txt.cpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#include "get_from_txt.hpp"

using namespace std;

int getNumberBlocs_from_text(ifstream& file){
    string line;
    int nb_blocs = 0;

    while(getline(file,line)){
        size_t found = line.find("pblock"); //Search lines with pblock
        if (found!= string::npos){
            nb_blocs++;
        }
    }
    return nb_blocs;
}

void getBlocs_from_text(std::ifstream& file, constraint *ctr)
{
    std::string line; //a line of the constraints file
    int i = 0;

    while (getline(file, line)) {
        size_t found = line.find("X0"); //Shearch lines with X or Y
        std::smatch matches; //matches
        std::string raw = R"(X\d*\s?\:\s*(\d{1,4})\s*Y\d*\s?\:\s*(\d{1,4})\s*\|\|\s*X\d{1,}\s?\:\s*(\d{1,3})\s*Y\d{1,}\s?\:\s*(\d{1,3}))"; //regular expression
        std::regex rgx;

        if (found!= string::npos){
            try
            {
                rgx = std::regex(raw);
            }
            catch (std::regex_error& e) //if it doesn't work
            {
                std::cout << "Error" << std::endl;
                std::cout << e.what() << std::endl;
            }

            if (std::regex_search(line, matches, rgx))
            {
                // matches[0] is the complete match
                ctr[i].X_down = matches[2].str(); //Group 2 : Get X0
                ctr[i].Y_down = matches[3].str(); //Group 3 : Get Y0
                ctr[i].X_up = matches[4].str(); //Group 4 : Get X1
                ctr[i].Y_up = matches[5].str(); //Group 5 : Get Y1
            }
            else{
                std::cout << "pblocks not found\n";
            }
            i++;
        }
    }
}

void getGen_from_text(std::ifstream& file, constraint *ctr)
{
    std::string line; //a line of the constraints file
    int i = 0;


    while (getline(file, line)) {
        size_t found = line.find("pblock"); //Shearch lines with add_cells_to_pblock
        std::smatch matches; //matches
        std::string raw3D = R"(pblock_(\d*)\s*\s*\(GEN_Z\[(\d{1,2})\]\s?GEN_Y\[(\d{1,2})\]\s?GEN_X\[(\d{1,2})\]\))"; //regular expression 3D
        std::string raw2D = R"(pblock_(\d*)\s*\s*\(GEN_Y\[(\d{1,2})\]\s?GEN_X\[(\d{1,2})\]\))"; //regular expression 2D
        std::regex rgx3D, rgx2D;

        if (found!= string::npos){
            try
            {
                rgx3D = std::regex(raw3D);
                rgx2D = std::regex(raw2D);
            }
            catch (std::regex_error& e) //if it doesn't work
            {
                std::cout << "Error" << std::endl;
                std::cout << e.what() << std::endl;
            }

            if (std::regex_search(line, matches, rgx3D))
            {
                // matches[0] is the complete match
                ctr[i].name = matches[1].str(); //Group 1 : get name
                ctr[i].GenZ = matches[2].str(); //Group 2 : Gen Z
                ctr[i].GenY = matches[3].str(); //Group 3 : Gen Y
                ctr[i].GenX = matches[4].str(); //Group 4 : Gen X
            }
            else{
                if (std::regex_search(line, matches, rgx2D))
                {
                    // matches[0] is the complete match
                    ctr[i].name = matches[1].str(); //Group 1 : get name
                    ctr[i].GenY = matches[2].str(); //Group 2 : Gen Y
                    ctr[i].GenX = matches[3].str(); //Group 3 : Gen X
                }
                //std::cout << "gen not found\n";
            }
            i++;
        }
    }
}