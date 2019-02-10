#include "file_tools.hpp"

using namespace std;

void SplitFilename (const std::string& str)
{
    size_t found = str.find_last_of("/\\");
    cout << "path: " << str.substr(0,found) << '\n';
    cout << "file: " << str.substr(found+1) << '\n';
}

std::string getFilename(const std::string& str){
    size_t lastindex = str.find_last_of(".");
    std::string filename = str.substr(0, lastindex);     // get file name WITHOUT extension
    return filename;
}

void SplitFilenameIntoFile(const std::string& str, std::ofstream& file_output)
{
    size_t found = str.find_last_of("/\\");
    file_output << "file: " << str.substr(found+1) << '\n';
    file_output << endl;
    file_output << endl;
}
