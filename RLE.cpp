#include <iostream>
#include "RLE.h"
using namespace std;

int RLE::compress(int8_t *data_ptr, int data_size)
{
  int trendCount = 0;       //length of a run of the same value
  int insertPos = 0;        //where to insert compressed data
  int8_t trend = data_ptr[0];   //the repeated value in a run

  for(int i = 0; i < data_size; i++)
  {
    if(data_ptr[i] == trend) //if we are encountering a run of the same value
    {
      trendCount ++;
    }
    
    if (data_ptr[i] != trend) //if a run has ended, by different value
    {
      insert(trendCount, data_ptr, insertPos, trend, trend);
    }
    if ( i == data_size - 1) //if we reached the end of the array
    {
      insert(trendCount, data_ptr, insertPos, trend, data_ptr[i]);
    }
    trend = data_ptr[i];  //update trend
  }

  if(insertPos < data_size) //if we have room at end (most times we will), insert length of original array (as a negative int) at end of our compressed array. This will help with decompression later.
  {
    int8_t x = -1;
    insert(data_size, data_ptr, insertPos, x, x); //this -1 is a dummy, we cleave it off the size at the end
    insertPos--;
  }
  return insertPos;
}

//helper function for insertion
void RLE::insert(int & trendCount, int8_t source[], int & insertPos, int8_t & trend, int8_t & insertion)
{
  if(trendCount > 1)  //if a run was ended, insert length of run, dented by negative sign, followed by the value in the run
  {
    while(trendCount > 127) // deal witn the case where there exist more than 127 contiguous copies of the same value
    {
      source[insertPos] = -1 * 127; // decrement by 127 at a time
      trendCount -= 127;
      insertPos += 1;
    }
    source[insertPos] = -1 * trendCount; // insert length of run as negative number
    source[insertPos + 1] = trend; //now insert the actual repeated value
    trendCount = 1; //reset the count
    insertPos += 2; // increment insertion positipn for the length and the value
  }
  else  //otherwise, if  we are not currently on a run, insert the last seen element 
  {
    source[insertPos] = insertion;
    trendCount = 1;
    insertPos ++;
  }
}

//takes the compressed array, its size, and where to decompress into (no in place decompression, sorry :p)
int RLE::decompress(int8_t * data_ptr, int size, int8_t *& sink)
{
  int insertPos = 0;
  int origSize = data_ptr[size - 1]; //get the saved length, if it exists
  if(origSize < 0)
  {
    origSize = 0;
    int i = size - 1;
    while(data_ptr[i] < 0)  // get all the negative numbers at end as length
    {
      origSize += -1 * data_ptr[i];
      i--;
      size --;
    }
  }
  else  //otherwise, length is original         
  {
    origSize = size;
  }
  sink = new int8_t[origSize]; //allocate the new array
  bool endOfLength = false;       //this indicates whether or not we have just finished retrieving the length of a run
  for(int i = 0; i < size; i++)
  {

    if(data_ptr[i] < 0) // if a length
    {
      endOfLength = true;
      int k = i;      //iterator to get actual value of run specified by length
      while (data_ptr[k] < 0)
      {
        k++;
      }
      for(int j = 0; j < data_ptr[i] * -1; j++) //fill in length number of value
      {
        sink[insertPos] = data_ptr[k];
        insertPos++;
      }
    }
    if(data_ptr[i] >= 0 && endOfLength)     //if we have reached the end of a run
    {
      endOfLength = false;
      continue;
    }
    if(data_ptr[i] >= 0)        //otherwise, if we encounter a solo value
    {
      sink[insertPos] = data_ptr[i];
      insertPos++;
      endOfLength = false;
    }
  }
  return origSize;
}

void print(int8_t source[], int size)
{
  for(int i = 0; i < size; i++)
  {
    cout <<  static_cast<int>(source[i]) << " ";
  }
  cout << endl;
}
