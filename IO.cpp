#include <iostream>
#include "IO.h"
#include <fstream>
#include <string>
using namespace std;

int8_t * IO::readRawData(string fileName, char delimiter)
{
    ifstream infile;
    infile.open (fileName);
    if (infile.is_open())
    {
        int size = 1;
        while (infile.good())
            if((char)infile.get() == delimiter)
                size++;
        int8_t rawData = new int8_t[size];
        infile.clear();
        infile.seekg(0, ios::beg);
        int i = 0;
        while (infile.good())
        {
            rawData[i] = infile.get();
            i++;
        }
        infile.close();
        return rawData;
    }
    cout << "Error opening file";
    return NULL;
}

int IO::rawSize()
{
    return rawSize;
}