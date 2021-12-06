#include "../Header_files/input.file.h"
bool InputFile::openFile(string paPath)
{
    file.open(paPath);
    return file.good();
}

bool InputFile::endOfFile()
{
    if (file.is_open() && file.eof())
        return true;
    return false;
}

void InputFile::nextLine()
{
    if (file.is_open()) {
        line.clear();
        string lineString;
        if (getline(file, lineString, '\n'))
            line.str(lineString);
    }
}

string InputFile::readWord()
{
    string word;
    if (getline(line, word, ';'))
        return word;
    throw std::exception("end of line reached!");
}

void InputFile::closeFile()
{
    if (file.is_open())
        file.close();
}


