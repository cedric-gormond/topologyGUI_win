#ifndef file_tools_hpp
#define file_tools_hpp

#include <cstdio>
#include <iostream>
#include <fstream>


/*
 * SplitFilename : display file's path and file's name
 */
void SplitFilename(const std::string& str);

/*
 * SplitFilename : display file's path and file's name
 */
std::string getFilename(const std::string& str);

/*
 * SplitFilenameIntoFile : write file's path and file's name into an output file
 */
void SplitFilenameIntoFile(const std::string& str, std::ofstream& file_output);

#endif /* file_tools_hpp */
