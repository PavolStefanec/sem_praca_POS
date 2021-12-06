#ifndef UNTITLED_INPUT_FILE_H
#define UNTITLED_INPUT_FILE_H
#pragma once
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class InputFile {
private:
    string fileName;
    fstream file;
    stringstream line;
public:
    bool openFile(string paPath);
    bool endOfFile();
    void nextLine();
    string readWord();
    void closeFile();
};
#endif //UNTITLED_INPUT_FILE_H
