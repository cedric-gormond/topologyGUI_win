//
//  create_output_file.cpp
//  topology
//
//  Created by Cedric Gormond on 25/01/2019.
//  Copyright © 2019 Cedric Gormond. All rights reserved.
//

#include "create_output_file.hpp"
#include "get_from_txt.hpp"

using namespace std;

void create_ctr_file(std::ofstream& file_output, string path,constraint *ctr, int size)
{
    cout << " * Wrinting in file " << endl << endl;
    
    //first line which create clock and its features
    file_output << "create_clock -period 5.000 -name clk -waveform {0.000 2.500} [get_ports Clock]" << endl;
    file_output << endl << endl;
    
    // string which contains the right expression of .GEN
    string set_gen;
    
    //Creation of a bloc
    for (int i=0; i < size; i++) {
        file_output << "create_pblock pblock_"<< ctr[i].name << endl;
        
        set_gen = setGen(ctr,i,size);
        
        file_output << "add_cells_to_pblock [get_pblocks pblock_"<< ctr[i].name <<"] [get_cells -quiet [list ";
        
        if (ctr[i].GenZ == "-1")
        {
            file_output <<"GEN_Y["<< ctr[i].GenY <<"].GEN_X["<< ctr[i].GenX <<"]"<< set_gen <<".Router}]]" << endl;
        } else {
            file_output << "{GEN_Z["<< ctr[i].GenZ <<"].GEN_Y["<< ctr[i].GenY <<"].GEN_X["<< ctr[i].GenX <<"]"<< set_gen <<".Router}]]" << endl;
        }
        
        file_output << "resize_pblock [get_pblocks pblock_"<< ctr[i].name <<"] -add {SLICE_X"<< ctr[i].X_down <<"Y"<< ctr[i].Y_down <<":SLICE_X"<< ctr[i].X_up <<"Y"<< ctr[i].Y_up <<"}" << endl;
        
        file_output << endl;
    }
    cout << " * Success " << endl << endl;
}

void create_txt_file(std::ofstream& file_output, string path,constraint *ctr, int size)
{
    cout << " * Wrtting in file " << endl << endl;
    for (int i=0; i < size; i++) {
        // PBLOC
        file_output << "pblock_" << ctr[i].name << "  (";
        
        //GEN
        if (ctr[i].GenZ != "-1") {
            file_output << "GEN_Z[" << ctr[i].GenZ << "] ";
        }
        file_output << "GEN_Y[" << ctr[i].GenY << "] ";
        file_output << "GEN_X[" << ctr[i].GenX << "]";
        file_output << ")  " << endl;
        
        // SLICES
        //file_output << endl;
        file_output << "X0 : "<<ctr[i].X_down << "\t" <<"Y0 : "<<ctr[i].Y_down;
        file_output << "\t  ||\t";
        file_output << "X1 : "<<ctr[i].X_up << "\t  " << "Y1 : "<<ctr[i].Y_up <<endl;
        file_output << endl;
    }
    cout << " * Success " << endl << endl;
}
