#include "LogFinder.h"

void LogFinder::OpenFile(const char* FilePath, std::ifstream& MyFile)
{
    MyFile.open(FilePath, std::ifstream::binary);
}

bool LogFinder::LowerTest(char LeftLetter, char RightLetter)
{
    return (std::tolower(LeftLetter) == std::tolower(RightLetter));
}

std::list<std::string> LogFinder::CaseSensitiveFind(std::ifstream& MyFile, std::string Word)
{
    std::string Line;
    std::list<std::string> MySearch;

    while (!MyFile.eof())
    {
        getline(MyFile, Line);
        if (Line.find(Word) != std::string::npos)
            MySearch.push_back(Line);
    }

    MyFile.close();
    return MySearch;
}

std::list<std::string> LogFinder::CaseInsensitiveFind(std::ifstream& MyFile, std::string Word)
{
    std::string Line;
    std::list<std::string> MySearch;

    while (!MyFile.eof())
    {
        getline(MyFile, Line);
        std::string::iterator look = (std::search(Line.begin(), Line.end(), Word.begin(), Word.end(), LogFinder::LowerTest));
        if( look != Line.end())
            MySearch.push_back(Line);
    }

    MyFile.close();
    return MySearch;
}

void LogFinder::ExportSearch(std::list<std::string> MySearch, std::string FilePath)
{
    std::ofstream ExportFile( FilePath.c_str() );
    for(std::list<std::string>::const_iterator i = MySearch.begin(); i != MySearch.end(); ++i)
        ExportFile << *i << "\n";
}




