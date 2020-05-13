#include <iostream>
#include "RLE.h"
#include "VERIFIER.h"
using namespace std;

int main() {
  int8_t  data    [4] = {3,1,1,2};

  RLE rle;
  VERIFIER verifier;

  int size = sizeof(data)/sizeof(data[0]);
  int8_t  verify  [size];
  for(int i = 0; i < size; i++)
  {
    verify[i] = data[i];
  }
  float origSize = size;
  // cout << "original data: ";
  // print(data, size);
  size = rle.compress(data, size);
  float compressedSize = size;
  cout << "compressed data: ";
  verifier.print(data, size);
  int8_t * sink = data;
  size = rle.decompress(data, size, sink);
  cout << "decompressed: ";
  verifier.print(sink, size);

  for (int i = 0; i < size; i++)
  {
    if (verify[i] != sink[i])
    {
      cout <<"compression ERROR";
      cout << i;
      cout << " " << static_cast<int16_t>(verify[i]) << " " << static_cast<int16_t>(sink[i]);
      return 0;
    }
  }
  if (compressedSize / origSize > 1)
  {
    cout <<"ERROR";
    return 0;
  }

  float ratio = compressedSize / origSize;
  cout << "no error" << endl;
  cout << "ratio of compressed to original is: " << ratio;
  return 0;
}
