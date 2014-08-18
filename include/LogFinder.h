#ifndef LOGFINDER_H_INCLUDED
#define LOGFINDER_H_INCLUDED

#include <list>
#include <string>
#include <locale>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace LogFinder
{


    void OpenFile(const char* FilePath, std::ifstream& MyFile);
    std::list<std::string> CaseSensitiveFind(std::ifstream& MyFile, std::string Word);
    std::list<std::string> CaseInsensitiveFind(std::ifstream& MyFile, std::string Word);

    void ExportSearch(std::list<std::string> MySearch, std::string FilePath);

    bool LowerTest(char LeftLetter, char RightLetter);
}


#endif // LOGFINDER_H_INCLUDED
