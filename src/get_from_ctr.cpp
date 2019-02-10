//
//  get_from_ctr.cpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#include "get_from_ctr.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int getNumberBlocsFromCtr(ifstream &file){
    string line;
    int nb_blocs = 0;
    
    while(getline(file,line)){
        size_t found = line.find("create_pblock"); //Search lines with create_block : create a router
        if (found!= string::npos){
            nb_blocs++;
        }
    }
    return nb_blocs;
}

void getBlocsFromCtr(std::ifstream &file, constraint *ctr)
{
    std::string line; //a line of the constraints file
    int i = 0;
    
    
    while (getline(file, line)) {
        size_t found = line.find("SLICE_X"); //Shearch lines with SLICEX
        std::smatch matches; //matches
        std::string raw = (R"(resize_pblock\s?\[get_pblocks\s?pblock_(\d{1,3})\]\s?\-\s?add[\n|\s]?\{SLICE_X(\d{1,4})Y(\d{1,4}):SLICE_X(\d{1,4})Y(\d{1,4})\})"); //regular expression
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
                ctr[i].name     = matches[1].str(); //Group 1 : Get the name of the block (pblock_i)
                ctr[i].X_down   = matches[2].str(); //Group 2 : Get X0
                ctr[i].Y_down   = matches[3].str(); //Group 3 : Get Y0
                ctr[i].X_up     = matches[4].str(); //Group 4 : Get X1
                ctr[i].Y_up     = matches[5].str(); //Group 5 : Get Y1
            }
            else{
                std::cout << "pblocks not found\n";
            }
            i++;
        }
    }
}

void getGenFromCtr(std::ifstream &file, constraint *ctr)
{
    std::string line; //a line of the constraints file
    int i = 0;
    
    bool is3D = true; // 3D default
    
    while (getline(file, line)) {
        size_t found = line.find("add_cells_to_pblock"); //Shearch lines with add_cells_to_pblock
        std::smatch matches; //matches
        
        std::string raw3D = (R"(add_cells_to_pblock\s?\[get_pblocks\s?pblock_\d*\]\s?\[get_cells\s?\-quiet\s?\[list[\n|\s?]\{GEN_Z\[(\d{1,2})\]\.GEN_Y\[(\d{1,2})\]\.GEN_X\[(\d{1,2})\])"); //regular expression for 3D gen
        
        std::string raw2D = (R"(add_cells_to_pblock\s?\[get_pblocks\s?pblock_\d*\]\s?\[get_cells\s?\-quiet\s?\[list[\n|\s?]\{GEN_Y\[(\d{1,2})\]\.GEN_X\[(\d{1,2})\])"); //regular expression for 2D gen
        
        std::regex rgx3D, rgx2D; //a regex for each case
        
        if (found!= string::npos){
            try
            {
                rgx2D = std::regex(raw2D);
                rgx3D = std::regex(raw3D);
            }
            catch (std::regex_error& e) //if it doesn't work
            {
                std::cout << "Error" << std::endl;
                std::cout << e.what() << std::endl;
            }
            
            if (std::regex_search(line, matches, rgx3D))
            {
                is3D = true;
                // matches[0] is the complete match
                ctr[i].GenZ = matches[1].str(); //Group 1 : Gen Z
                ctr[i].GenY = matches[2].str(); //Group 2: Gen Y
                ctr[i].GenX = matches[3].str(); //Group 3 : Gen X
            }
            else
            {
                if (std::regex_search(line, matches, rgx2D)) {
                    is3D = false;
                    // matches[0] is the complete match
                    ctr[i].GenY = matches[1].str(); //Group 1 : Gen Y
                    ctr[i].GenX = matches[2].str(); //Group 2: Gen X
                }
                //std::cout << "gen not found\n";
            }
            i++;
        }
    }
    //display dimensions in console
    if (is3D) {
        cout << " * 3D dectected" << endl << endl;
    } else {
        cout << " * 2D dectected" << endl << endl;
    }
    
}

void displayBlocsFromCtr(constraint *ctr, int size)
{
    for (int i=0; i < size; i++) {
        // PBLOC
        cout << "pblock_" << ctr[i].name << "  | ";
        
        //GEN
        if (ctr[i].GenZ != "-1") {
            cout << " GEN_Z[" << ctr[i].GenZ << "]"; // 2D case
        }
        cout << " GEN_Y[" << ctr[i].GenY << "]";
        cout << " GEN_X[" << ctr[i].GenX << "]";
        cout << endl;
        
        // SLICES
        cout << "X0      : "<<ctr[i].X_down <<endl;
        cout << "Y0      : "<<ctr[i].Y_down <<endl;
        cout <<endl;
        cout << "X1      : "<<ctr[i].X_up <<endl;
        cout << "Y1      : "<<ctr[i].Y_up <<endl;
        cout << endl;
        
        //CENTER
        cout << "(Xc,Yc) :" << " ( " << ctr[i].CenterX << " , "<< ctr[i].CenterY << " ) " << endl << endl;
    }
}
