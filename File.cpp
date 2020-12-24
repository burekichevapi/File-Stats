#include "File.hpp"

File File::openFile(const std::string fileName)
{
    File f(fileName);

    return f;
}

File::File(const std::string fileName)
{
    fileStream->open(fileName, std::ios::in | std::ios::out);

    if (!canOpen())
        return;

    fileContent = readFile();
}

File File::createFile(const std::string fileName, const std::string contents)
{
    File f(fileName, contents);

    return f;
}

File::File(const std::string fileName, const std::string content)
{
    fileStream->open(fileName, std::ios::in | std::ios::out | std::ios::trunc);

    if (!canOpen())
        return;

    *fileStream << content;

    fileContent = content;

    resetStream();
}

File::~File()
{
    fileStream->flush();
    fileStream->close();
    delete fileStream;
    fileStream = nullptr;
}

std::string File::readFile()
{
    std::string stringBuilder;

    while (*fileStream)
    {
        std::string line;
        std::getline(*fileStream, line);

        fileStream->seekg(-1, std::ios::cur);
        line += fileStream->get();
        stringBuilder += line;
    }

    resetStream();

    return stringBuilder;
}

bool File::canOpen()
{
    return fileStream->is_open();
}

std::string File::getContent()
{
    return fileContent;
}

std::fstream* File::getStream()
{
    resetStream();

    return fileStream;
}

void File::resetStream()
{
    fileStream->clear();
    fileStream->seekg(0);
}