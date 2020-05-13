#include <iostream>
#include "VERIFIER.h"
using namespace std;

VERIFIER::VERIFIER()
{
  step = 0;
}

void VERIFIER::print(int8_t source[], int size)
{
  for(int i = 0; i < size; i++)
  {
    cout <<  static_cast<int>(source[i]) << " ";
  }
  cout << endl;
}