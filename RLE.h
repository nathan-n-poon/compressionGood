#include <iostream>
using namespace std;

class RLE
{
    public:
        int compress(int8_t *data_ptr, int data_size);
        int decompress(int8_t * data_ptr, int size, int8_t *& sink);
        void print(int8_t source[], int size);
    private:
        void insert(int & trendCount, int8_t source[], int & insertPos, int8_t & trend, int8_t & insertion);
};