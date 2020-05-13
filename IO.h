#include <iostream>
using namespace std;

class IO
{
    public:
        int8_t * readRawData(string filename, char delimiter);
        int rawSize();
    private:
        int rawSize;
};