//C++ libraries
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

//GUI Library
#include "imgui.h"
#include "imgui-SFML.h"

//Framework
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

//Source files
#include "block.h"
#include "blockContainer.h"
#include "lineContainer.h"
#include "ctr.hpp"
#include "get_from_ctr.hpp"
#include "file_tools.hpp"
#include "topology.hpp"
#include "create_output_file.hpp"
#include "surface.h"

#include "get_time.h"
#include "log.h"


using namespace std;

//Global
string current_time;

int main() {
    /*
     * ---------------------------------------------------------------
     *                INPUT FILE
     * ---------------------------------------------------------------
     */
    //Please past the path's file ;"/Users/cedricgormond/Desktop/topologyGUI/fichier_contrainte_2D.txt"
    string file_path = "io/fichier_contrainte_2D.txt"; //FULL PATH

    ifstream file(file_path.c_str(), ios::in);
    string input_filename = getFilename(file_path); // get the input file name WITHOUT extension

    if (file) {
        cout << " * File found :" << endl;
        SplitFilename(file_path);
    }
    else {
        cout << " * Cannot find  :" <<endl;
        SplitFilename(file_path);

        cout << endl << " * The constraint file must be named : fichier_contrainte_2D.txt \n \n";
        cout << " * Exit" <<endl<<endl;

        exit (EXIT_FAILURE);
    }

    /*
    * ---------------------------------------------------------------
    *                READ INPUT FILE AND EXTRACT BLOCS
    * ---------------------------------------------------------------
    */
    //Get number of routers (blocs)
    cout << endl;
    cout << " * Searching for pblocs " << endl;
    int nb_pblocs = getNumberBlocsFromCtr(file);
    cout << " * " <<nb_pblocs << " pblocs found \n";
    cout << endl;
    file.close();

    //Constraint values
    auto *CONTRAINT = new constraint[nb_pblocs];
    initConstraint(CONTRAINT);

    // Get all the routers (pblocs)
    file.open(file_path);
    getBlocsFromCtr(file, CONTRAINT);
    file.close();

    // Get all the generation of each (pblocs)
    file.open(file_path);
    getGenFromCtr(file, CONTRAINT);
    file.close();

    // Set the center of all blocs
    dimensions_of_bloc(CONTRAINT, nb_pblocs);

    // Display blocs in console
    //displayBlocsFromCtr(CONTRAINT, nb_pblocs);

    //Resize constraint
    auto *CONTRAINT_RESIZE = new constraint[nb_pblocs];
    initConstraint(CONTRAINT_RESIZE);
    CONTRAINT_RESIZE = CONTRAINT; //copy

    // ------ OUTPUT FILE ------
    const string &output_path = input_filename;
    ofstream file_output;

    /*
     * ---------------------------------------------------------------
     *                             SFML
     * ---------------------------------------------------------------
     */
    //Init SFML
    //Window settings
    sf::RenderWindow window(sf::VideoMode(700, 800), "topologyGUI", sf::Style::Close);
    window.setFramerateLimit(30);

    // Clock
    sf::Clock deltaClock;

    /*
     * ---------------------------------------------------------------
     *                             SFML/IMGUI
     * ---------------------------------------------------------------
     */
    //Init ImGUI
    ImGui::SFML::Init(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //Theme and frame rounding
    ImGui::StyleColorsLight();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);

    // ImGUI - variables
    static ExampleAppLog my_log;
    my_log.AddLog("%s [info] Welcome \n", &current_time[0]);
    static auto * p_open = new bool;
    *p_open = true;

    //Font
    ImFont* font = io.Fonts->AddFontFromFileTTF("misc/fonts/Roboto-Regular.ttf", 16.0, nullptr);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("misc/fonts/OpenSans-Regular.ttf", 17.0, nullptr);
    ImGui::SFML::UpdateFontTexture(); // important call: updates font texture

    /*
     * ---------------------------------------------------------------
     *                             SFML Objects
     * ---------------------------------------------------------------
     */
    // create container with nb_pblocs blocks in it, starting at pos 100/100
    // this container will be drawn using ContainerOfBlocks' void drawContainer(sf::RenderWindow &window)
    // ContainerOfBlocks Blocks(nb_pblocs, sf::Vector2f(100, 100),CONTRAINT_RESIZE);

    // create  line container, starting at pos 100/100
    // this container will be drawn using ContainerOfLines' void drawContainer(sf::RenderWindow &window)
    // ContainerOfLines lines(nb_pblocs, sf::Vector2f(150.0f, 100.0f), CONTRAINT_RESIZE,100);

    /*
     *  User's variables
     */
    static int distance2D    =  100;
    static int distance3D    =  100;
    static int diagonal      =  100;
    static bool is3D         =  false;
    int surface_2D =0;
    int surface_hexa =0;
    int surface_3D = 0;


    /*
     * ---------------------------------------------------------------
     *                      MAIN LOOP
     * ---------------------------------------------------------------
     */
    // Infinite loop
    while (window.isOpen()) {
        current_time = currentDateTime(); //get time
        sf::Event evt;
        while (window.pollEvent(evt)) {
            ImGui::SFML::ProcessEvent(evt);

            //ContainerOfLines lines(nb_pblocs, sf::Vector2f(150.0f, 100.0f), CONTRAINT_RESIZE,distance);

            if (evt.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        /*
         * ---------------------------------------------------------------
         *                      ImGUI - User Interface
         * ---------------------------------------------------------------
         */
        ImGui::PushFont(font);
        /*
         *  Begin main window
         */
        ImGui::Begin("Settings",p_open,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::Text("Current file : %s", &input_filename[0]);

        /*
         *  Help section
         */
        if (ImGui::CollapsingHeader("Help")) {
            ImGui::BulletText("TopologyGUI doesn't recognize .xdc files ");
            ImGui::BulletText("TopologyGUI can only generate constraint files with their respective dimensions. \n");
            ImGui::BulletText("TopologyGUI can only create 2D constraint files. \n");
        }
        ImGui::Separator();

        /*
         *  Open file
         */
        if (ImGui::CollapsingHeader("Open file"))
        {
            ImGui::BulletText("WIP (à faire un collapsed ou en menu)");
            /*
            if (file) {
                my_log.AddLog("%s [info] File found : \n", &current_time[0]);
                my_log.AddLog("%s",&file_path[0]);
            }
            else {
                my_log.AddLog("%s [error] Cannot find  :",&current_time[0]);
                my_log.AddLog("%s",&file_path[0]);

                my_log.AddLog("%s [suggest] The constraint file must be named : fichier_contrainte_2D.txt \n",&current_time[0]);
                my_log.AddLog("%s [info] Exit : \n", &current_time[0]);
            }
             */
        }

        /*
         *  Generate simplified constraint file without any modification
         */
        ImGui::Text("Generate simplified constraint file without any modification");
        if (ImGui::Button("Generate simplified constraint file "))     {
            std::string output_path_temp = output_path + "_original_simplified.txt";

            //Writing
            file_output.open(output_path_temp);
            create_txt_file(file_output, file_path, CONTRAINT, nb_pblocs);
            file_output.close();

            //log
            my_log.AddLog("%s [info] [default] Generate simplified constraint file \n", &current_time[0]);
            my_log.AddLog("%s [info] [default] Success \n",&current_time[0]);
            my_log.AddLog("%s [info] [default] Output file : %s \n", &current_time[0],&output_path_temp[0]);
        }
        ImGui::SameLine();
        ShowHelpMarker("Generate a simplified constraint file which is NOT compatible with Xilinx Vivado\n");
        ImGui::Separator();

        /*
         *  Create constraint file from scratch
         */
        static bool disabled = true;
        static int gens[3] = { 3, 3, -1 }; // X0 Y0 X1 Y1
        static int coord[4] = { 10, 10 , 20, 20}; // X0 Y0 X1 Y1
        if (ImGui::CollapsingHeader("Create constraint file from scratch"))
        {
            ImGui::Checkbox("Disable", &disabled);
            if (disabled)   ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.43f);
                if (is3D){
                    gens[2] = 1;
                    ImGui::Text("DimX :                               "); ImGui::SameLine();
                    ImGui::Text("DimY :                               "); ImGui::SameLine();
                    ImGui::Text("DimZ : (always 1)");
                    ImGui::SameLine();
                    ShowHelpMarker("DimZ should be between 0 and 1. \n");
                    ImGui::PushID(1);
                    ImGui::InputInt3("##", gens);
                    gens[2] = 1; // we force the value
                    ImGui::PopID(); ImGui::SameLine();
                    ImGui::Text("%d blocs", gens[0]*gens[1]*(gens[2]+1));
                } else {
                    gens[2] = -1;
                    ImGui::Text("DimX :              "
                                "                    "
                                "                    "); ImGui::SameLine();
                    ImGui::Text("DimY : ");
                    ImGui::PushID(1);
                    ImGui::InputInt2("##", gens);
                    ImGui::PopID(); ImGui::SameLine();
                    ImGui::Text("%d blocs", gens[0]*gens[1]);
                }

                ImGui::Text("X0 :           "
                            "               "); ImGui::SameLine();
                ImGui::Text("Y0 :          "
                            "               "); ImGui::SameLine();
                ImGui::Text("X1 :          "
                            "              "); ImGui::SameLine();
                ImGui::Text("Y1 : ");
                ImGui::InputInt4("##", coord); ImGui::SameLine();
                ImGui::Text("(W : %d, H : %d) ", abs(coord[0] - coord[2]), abs(coord[1] - coord[3]));

            if (disabled)   ImGui::PopStyleVar();

        }
        ImGui::Separator();

        /*
         *  Topology
         */
        static int d;
        static int choice_topology; //Choose your topology
        if (ImGui::CollapsingHeader("Topology"))
        {
            ImGui::Text("Choose your topology :");
            ImGui::RadioButton("2D Mesh", &choice_topology, 1); ImGui::SameLine();
            ImGui::RadioButton("2D Hexa", &choice_topology, 2); ImGui::SameLine();
            ImGui::RadioButton("3D Mesh", &choice_topology, 3);

            switch(choice_topology) {
                case 1 :
                    ImGui::PushID(1);
                    ImGui::Text("Distance in slices between each block : ");
                    ImGui::InputInt("",&distance2D);
                    ImGui::PopID();
                    is3D = false;
                    break;
                case 2 :
                    ImGui::PushID(1);
                    ImGui::Text("Diagonal 'r' in slices : ");
                    ImGui::InputInt("",&diagonal); ImGui::SameLine();
                    d = static_cast<int>(diagonal * cos(30 * 3.14 / 180));
                    ImGui::Text("d : %d", d);
                    ImGui::PopID();
                    is3D = false;
                    break;
                case 3 :
                    ImGui::PushID(1);
                    ImGui::Text("Distance in slices between each block : ");
                    ImGui::InputInt("",&distance3D);
                    ImGui::Text("ATTENTION ! TopologyUI can only handle two Z generations (from 0 to 1)");
                    ImGui::PopID();
                    is3D = true;
                    break;
                default:
                    break;
            }
        }
        ImGui::Separator();

        /*
         *  Dimensions
         */
        // Resize dimensions
        static int choice_resize = 0;
        static int vec2i[2] = { 10, 10 };
        static int default2i[2] = { CONTRAINT[0].width, CONTRAINT[0].heigth};

        if (ImGui::CollapsingHeader("Dimensions"))
        {
            ImGui::RadioButton("Use default size", &choice_resize, 1);ImGui::SameLine();
            ImGui::RadioButton("Resize every pblock", &choice_resize, 2);

            switch (choice_resize) {
                case 1 :
                    ImGui::Text("(%d , %d)", default2i[0],default2i[1] );
                    break;

                case 2:
                    //Width
                    ImGui::PushID(2);
                    ImGui::Text("Width :                         "); //nasty spacing (^.^)
                    ImGui::SameLine();
                    ImGui::Text("Heigth : ");
                    ImGui::InputInt2("##", vec2i);
                    ImGui::PopID();
                    break;

                default:
                    break;
            }
        }
        ImGui::Separator();

        /*
         *  Generate constraint file
         */
        ImGui::Text("Save constraint file as ");
        const char* items[] = { ".txt", ".xdc"};
        static int choice_type = 0;
        ImGui::Combo("", &choice_type, items, IM_ARRAYSIZE(items));
        auto *CONTRAINT_CREATED = new constraint[gens[0]*gens[1]];

        if (ImGui::Button("Generate constraint file"))     {
            std::string output_path_temp;
            // switch topology
            switch(choice_topology) {
                case 1 :
                    //check resize dimensions
                    if(choice_resize == 2){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [mesh2D] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    } else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }

                    //apply topology
                    if (disabled){
                        CONTRAINT_RESIZE = set2D(CONTRAINT_RESIZE, distance2D, nb_pblocs);
                        surface_2D = getSurface2D(CONTRAINT_RESIZE, distance2D, nb_pblocs);
                    }
                    else{
                        my_log.AddLog("%s [info] [mesh2D] Input file ignored \n", &current_time[0]);
                        CONTRAINT_CREATED = createConstraint(gens, coord);
                        CONTRAINT_CREATED = set2D(CONTRAINT_CREATED, distance2D, gens[0] * gens[1]);
                        surface_2D = getSurface2D(CONTRAINT_CREATED, distance2D, gens[0] * gens[1]);
                    }

                    //Writing
                    if (choice_type == 0) output_path_temp = output_path + "_generated.txt";
                    if (choice_type == 1) output_path_temp = output_path + "_generated.xdc";
                    file_output.open(output_path_temp);
                    if (disabled)   create_ctr_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    else    create_ctr_file(file_output, file_path, CONTRAINT_CREATED, gens[0]*gens[1]);
                    file_output.close();

                    //log
                    my_log.AddLog("%s [info] [mesh2D] Generate constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [mesh2D] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [mesh2D] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;
                case 2 :
                    //check resize dimensions
                    if(choice_resize == 2){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [hexa] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    }else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }

                    //apply topology
                    if (disabled){
                        CONTRAINT_RESIZE = setHexa(CONTRAINT_RESIZE, diagonal, nb_pblocs);
                        surface_hexa = getSurfaceHexa(CONTRAINT_RESIZE, diagonal, nb_pblocs);
                    }
                    else{
                        my_log.AddLog("%s [info] [hexa] Input file ignored \n", &current_time[0]);
                        CONTRAINT_CREATED = createConstraint(gens, coord);
                        CONTRAINT_CREATED = setHexa(CONTRAINT_CREATED, diagonal, gens[0] * gens[1]);
                        surface_hexa = getSurfaceHexa(CONTRAINT_CREATED, diagonal, gens[0] * gens[1]);
                    }

                    //Writing
                    if (choice_type == 0) output_path_temp = output_path + "_hexa_generated.txt";
                    if (choice_type == 0) output_path_temp = output_path + "_hexa_generated.txt";
                    if (choice_type == 1) output_path_temp = output_path + "_hexa_generated.xdc";
                    file_output.open(output_path_temp);
                    if (disabled)   create_ctr_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    else    create_ctr_file(file_output, file_path, CONTRAINT_CREATED, gens[0]*gens[1]);
                    file_output.close();

                    //log
                    my_log.AddLog("%s [info] [hexa] Generate constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [hexa] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [hexa] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;
                case 3:
                    //check resize dimensions
                    if(choice_resize == 3){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [mesh3D] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    } else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }

                    //apply topology
                    if (disabled){
                        CONTRAINT_RESIZE = set3D(CONTRAINT_RESIZE, distance3D, nb_pblocs);
                        surface_3D = getSurface3D(CONTRAINT_RESIZE, distance3D, nb_pblocs);
                    }
                    else{
                        my_log.AddLog("%s [info] [mesh3D] Input file ignored \n", &current_time[0]);
                        CONTRAINT_CREATED = createConstraint3D(gens, coord);
                        CONTRAINT_CREATED = set3D(CONTRAINT_CREATED, distance3D, gens[0] * gens[1] * (gens[2] + 1));
                        surface_3D = getSurface3D(CONTRAINT_CREATED, distance3D, gens[0] * gens[1] * (gens[2] + 1));
                    }

                    //Writing
                    if (choice_type == 0) output_path_temp = output_path + "_3D_generated.txt";
                    if (choice_type == 1) output_path_temp = output_path + "_3D_generated.xdc";
                    file_output.open(output_path_temp);
                    if (disabled)   create_ctr_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    else    create_ctr_file(file_output, file_path, CONTRAINT_CREATED, gens[0]*gens[1]*(gens[2]+1));
                    file_output.close();

                    //log
                    my_log.AddLog("%s [info] [mesh3D] Generate constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [mesh3D] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [mesh3D] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;
                default:
                    my_log.AddLog("%s [error] Please choose a topology\n", &current_time[0]);
                    break;
            }
        }

        /*
         *  Generate constraint file (simplified)
         */
        if (ImGui::Button("Generate constraint file (simplified)"))     {
            std::string output_path_temp;
            switch(choice_topology) {

                case 1:
                    //check resize dimensions
                    if(choice_resize == 2){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [mesh2D] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    }else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }

                    //apply topology
                    CONTRAINT_RESIZE = set2D(CONTRAINT_RESIZE, distance2D, nb_pblocs);

                    //Writing
                    file_output.open(output_path_temp);
                    create_txt_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    file_output.close();

                    //log
                    output_path_temp = output_path + "_simplified_generated.txt";
                    my_log.AddLog("%s [info] [mesh2D] Generate simplified constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [mesh2D] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [mesh2D] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;

                case 2:
                    //check resize dimensions
                    if(choice_resize == 2){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [hexa] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    }else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }
                    //apply topology
                    CONTRAINT_RESIZE = setHexa(CONTRAINT_RESIZE, diagonal, nb_pblocs);

                    //Writing
                    output_path_temp = output_path + "_simplified_generated.txt";
                    file_output.open(output_path_temp);
                    create_txt_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    file_output.close();

                    //log
                    my_log.AddLog("%s [info] [hexa] Generate simplified constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [hexa] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [hexa] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;
                case 3:
                    //check resize dimensions
                    if(choice_resize == 3){
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, vec2i);
                        my_log.AddLog("%s [info] [mesh3D] Resize every blocs to (%d,%d) \n", &current_time[0], vec2i[0], vec2i[1]);
                    } else {
                        resize_dimensions(CONTRAINT_RESIZE, nb_pblocs, default2i);
                    }
                    //apply topology
                    CONTRAINT_RESIZE = set3D(CONTRAINT_RESIZE, distance3D, nb_pblocs);

                    //Writing
                    output_path_temp = output_path + "_simplified_generated.txt";
                    file_output.open(output_path_temp);
                    create_txt_file(file_output, file_path, CONTRAINT_RESIZE, nb_pblocs);
                    file_output.close();

                    //log
                    my_log.AddLog("%s [info] [mesh3D] Generate simplified constraint file \n", &current_time[0]);
                    my_log.AddLog("%s [info] [mesh3D] Success \n",&current_time[0]);
                    my_log.AddLog("%s [info] [mesh3D] Output file : %s \n", &current_time[0],&output_path_temp[0]);
                    break;

                default:
                    my_log.AddLog("%s [error] Please choose a topology\n", &current_time[0]);
                    break;
            }
        }
        ImGui::SameLine();
        ShowHelpMarker("Generate a simplified constraint file which is NOT compatible with Xilinx Vivado\n");
        ImGui::Separator();

        /*
         *  SURFACE
         */
        static int D_2D = 0;
        static int R_2D = 0;
        static int D_3D = 0;
        static int user_surface = 0;
        static int user_distance;
        if (ImGui::CollapsingHeader("Surface"))
        {
            ImGui::Separator();
            ImGui::Text("Surface 2D (slices)   : %d ", surface_2D);
            ImGui::Text("Surface Hexa (slices) : %d ", surface_hexa);
            ImGui::Text("Surface 3D (slices)   : %d ", surface_3D);

            ImGui::Separator();

            ImGui::PushID(4);
            ImGui::Text("Input surface S :"); ImGui::SameLine();
            ImGui::InputInt("", &user_surface);
            ImGui::SameLine();
            ShowHelpMarker("Calculate distance 'd' or 'r' from the input surface by using parameters of the third section\n");
            ImGui::RadioButton("Distance 'd' from surface S (2D Mesh)", &user_distance, 1); ImGui::SameLine();
            ImGui::Text(" : %d", D_2D);
            ImGui::RadioButton("Distance 'r' from surface S (2D Hexa)", &user_distance, 2); ImGui::SameLine();
            ImGui::Text(" : %d", R_2D);
            ImGui::RadioButton("Distance 'd' from surface S (3D Mesh)", &user_distance, 3); ImGui::SameLine();
            ImGui::Text(" : %d", D_3D);
            ImGui::PopID();

            if(ImGui::Button("Get Distance")){
                D_2D = getDfromS2D(gens, coord, user_surface);
                R_2D = getDfromSHexa(gens, coord, user_surface);
                D_3D = getDfromS3D(gens, coord, user_surface);
                my_log.AddLog("%s [info] [surface] Calculate distances from surface S \n", &current_time[0]);
            }

            ImGui::SameLine();

            if(ImGui::Button("Apply selected distance")){
                switch (user_distance){
                    case 1:
                        distance2D = D_2D;
                        my_log.AddLog("%s [info] [mesh2D] Apply selected distance : %d \n", &current_time[0], D_2D);
                        break;
                    case 2:
                        diagonal = R_2D;
                        my_log.AddLog("%s [info] [hexa] Apply selected distance : %d \n", &current_time[0], R_2D);
                        break;
                    case 3:
                        distance3D = D_3D;
                        my_log.AddLog("%s [info] [mesh3D] Apply selected distance : %d \n", &current_time[0], D_3D);
                        break;
                }
            }
        }
        ImGui::Separator();

        /*
         *  LOG
         */
        ImGui::Text("Log :"); ImGui::SameLine();
        my_log.DrawInCurrentWindow("Log");

        ImGui::End(); // end window

        /*
         *  RENDER
         */
        window.clear();
        ImGui::PopFont();
        ImGui::SFML::Render(window);

        //window.draw(Blocks); //OR Blocks.drawContainer(window);
        //window.draw(lines);
        window.display();
    }

    ImGui::SFML::Shutdown();
    cout << "* Exit"<<endl;

    //delete []CONTRAINT;
    //delete []CONTRAINT_RESIZE;
    return 0;
}