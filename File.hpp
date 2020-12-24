
#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

class File
{
private:
    std::fstream* fileStream = new std::fstream();

    std::string fileContent;

    std::string readFile();

    File(const std::string filename);

    File(const std::string fileName, const std::string content);

public:

    ~File();

    bool canOpen();

    std::string getContent();

    std::fstream* getStream();

    void resetStream();

    static File openFile(const std::string fileName);

    static File createFile(const std::string fileName, const std::string contents);
};


#endif
