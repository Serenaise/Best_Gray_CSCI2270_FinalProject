#include "HashTable.h"
#include <iostream>
#include <math.h>
#include <stdint.h>

using namespace std;

HashTable::HashTable(int _size)
{
  //ctor
  tableSize = _size;
  collisions = 0;
  //hashTable = new HashElem*[tableSize];
  initToNull();
}
HashTable::~HashTable()
{
  delete hashTable;
  //dtor
}
/*I think that most of these functions should work but I'm not sure.
They almost certaintly need work.*/

//added hashTable declaration here, still needs to delete each element of array
void HashTable::initToNull()
{
  hashTable = new HashElem*[tableSize];
  for(int x = 0; x < tableSize; x++)
  {
    hashTable[x] = NULL;
  }
}
void HashTable::setTableSize(int newsize){
  tableSize = newsize;
  initToNull();
}
void HashTable::insertSum(string name)
{
  int index = hashSum(name, tableSize);
  HashElem *current;
  HashElem *elk = new HashElem(name);
  if (hashTable[index] == NULL)
  {
    hashTable[index] = elk;
  }
  else
  {
    current = hashTable[index];
    while (current -> next != NULL)
    {
      current = current -> next;
    }
    current -> next = elk;
    elk -> previous = current;
  }
}
void HashTable::insertMul(string name)
{
  int index = hashMultiply(name, tableSize);
  HashElem *current;
  HashElem *elk = new HashElem(name);
  if (hashTable[index] == NULL)
  {
    hashTable[index] = elk;
  }
  else
  {
    current = hashTable[index];
    while (current -> next != NULL)
    {
      current = current -> next;
    }
    current -> next = elk;
    elk -> previous = current;
  }
}
void HashTable::deleteSum(std::string name)
{
  HashElem *current = NULL;
  HashElem *toDel = NULL;
  int index = hashSum(name, tableSize);
  current = hashTable[index];
  if (current == NULL)
  {
    return;
  }
  if (current -> title == name)
  {
    cout << "Here" << endl;
    current = NULL;
    delete current;
  }
  else
  {
    while (current -> title != name && current -> next != NULL)
    {
      current = current -> next;
    }
    if (current -> title == name)
    {
      current -> previous -> next = current -> next;
      current -> next -> previous = current -> previous;
      delete current;
    }
  }
}
void HashTable::deleteMul(std::string name)
{
  HashElem *current = NULL;
  HashElem *toDel = NULL;
  int index = hashMultiply(name, tableSize);
  current = hashTable[index];
  if (current == NULL)
  {
    return;
  }
  if (current -> title == name)
  {
    cout << "Here" << endl;
    current = NULL;
    delete current;
  }
  else
  {
    while (current -> title != name && current -> next != NULL)
    {
      current = current -> next;
    }
    if (current -> title == name)
    {
      current -> previous -> next = current -> next;
      current -> next -> previous = current -> previous;
      delete current;
    }
  }
}
void HashTable::find(std::string name)
{
  HashElem *current = NULL;
  int index = hashSum(name, tableSize);
  current = hashTable[index];
  while (current -> title != name)
  {
    current = current -> next;
  }
  if (current -> title == name)
  {
    cout << index << ":" << current -> title << endl;
    return;
  }
  cout << "not found" << endl;
}
void HashTable::printTableContents()
{
  HashElem *current = NULL;
  bool empty = true;
  for (int i = 0; i < tableSize; i++)
  {
    if (hashTable[i] != NULL)
    {
      empty = false;
      current = hashTable[i];
      cout <<current->title<<endl;
      while(current -> next != NULL)
      {
        current = current -> next;
        cout<<current->title<<endl;
      }
    }
  }
  if (empty == true)
  {
    cout << "empty" << endl;
  }
}
/*The hashSum and hashMultiply functions _should_ be working but
I haven't tested them very throughly*/
int HashTable::hashSum(string s, int x)
{
  int sum = 0;
  for (int i = 0; i < s.size(); i++)
  {
    sum = sum + s[i];
  }
  sum = sum % x;
  return sum;
}
int HashTable::hashMultiply(string k, int sz)
{
  int sum;
  double A, kA, fracpart,intpart;/*intpart is originally the integer
  part of kA but is then cannibalized and used as a place to store the return value*/
  A = 13/32;
  for (int i = 0; i < k.size(); i++)
  {
    sum = sum + k[i];
  }
  kA = sum * A;
  fracpart = modf(kA,&intpart);
  intpart = fracpart * tableSize;
  intpart = floor(intpart);
  return intpart;
}
/*This function does not work*/
void HashTable::SHA1(string message, uint32_t hh[5])
/*
SHA1("")
gives hexadecimal: da39a3ee5e6b4b0d3255bfef95601890afd80709
*/
{
  union {
    uint64_t Int64;
    char Chars[sizeof(uint64_t)];
  } var;
  uint32_t h0 = 0x67452301;
  uint32_t h1 = 0xEFCDAB89;
  uint32_t h2 = 0x98BADCFE;
  uint32_t h3 = 0x10325476;
  uint32_t h4 = 0xC3D2E1F0;
  uint64_t ml = (message.length())*8;/*The message length in bits*/
  message.push_back(0x80);
  while ((message.length()*8)%512 != 448)
  {
    cout << "Before: " << message.length() << endl;
    message.push_back(0x00);
    cout << "After: " << message.length() << endl;
  }
  ml = htobe64(ml);
  var.Int64 = ml;
  for(int i = 0; i < sizeof(uint64_t); ++i)
  {
    message.push_back(var.Chars[i]);
  }
  vector <vector <uint8_t> > ChunkV;
  size_t ChunkOffset;
  for (int x = 0; x < message.length()/64; x++)
  {
    vector <uint8_t> chunk;
    ChunkOffset = x * 64;
    for (int byteI = 0; byteI < 64; ++byteI)
    {
      chunk.push_back(message[ChunkOffset + byteI]);
      //cout << "Pushing: " << (unsigned int)message[ChunkOffset + byteI] <<endl;
    }
    ChunkV.push_back(chunk);
  }
  //uint32_t w[16];
  for (int CI = 0; CI < ChunkV.size(); CI ++)
  {
    for (int ci = 0; ci < ChunkV[CI].size(); ci++)
    {
      cout << (int)ChunkV[CI][ci] << endl;
    }
  }
  for(int x = 0; x < ChunkV.size(); ++x)
  {
    uint32_t w[80];
    /*uint32_t *wordptr;
    wordptr = (uint32_t*)&ChunkV[x][0];
    w[i] = *wordptr;*/
    for(int i = 0,j = 0; i < 64; i += 4, j++)
    {
      w[j] = 0;
      w[j] = ((uint32_t)ChunkV[x][i]) << 24 | ((uint32_t)ChunkV[x][i + 1]) << 16 | ((uint32_t)ChunkV[x][i + 2]) << 8 | ((uint32_t)ChunkV[x][i + 3]);
      w[j] = htobe32(w[j]);
    }
    for (int i = 16; i < 80; i++)
    {
      w[i] = leftRotate((w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]),1);
    }
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f;
    uint32_t k;
    uint32_t temp;
    for (int i = 0; i < 80; ++i)
    {
      if (0 <= i <= 19)
      {
        f = (b & c) | ((~b) & d);
        k = 0x5A827999;
      }
      else if (20 <= i <= 39)
      {
        f = b ^ c ^ d;
        k = 0x6ED9EBA1;
      }
      else if (40 <= i <= 59)
      {
        f = (b & c) | (b & d) | (c & d);
        k = 0x8F1BBCDC;
      }
      else if (60 <= i <= 79)
      {
        f = b ^ c ^ d;
        k = 0xCA62C1D6;
      }

    temp = (leftRotate(a,5) + f + e + k + w[i]);
    e = d;
    d = c;
    c = leftRotate(b,30);
    b = a;
    a = temp;
    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    }
  }
  hh[5];
  hh[0] = h0;
  hh[1] = h1;
  hh[2] = h2;
  hh[3] = h3;
  hh[4] = h4;
}
uint32_t HashTable::leftRotate(uint32_t val, int itt)
{
  val = be32toh(val);
  bool b;
  for (int x = 0; x < itt; x++)
  {
    b = (0 != (val & (1 << 31)));
    val <<= 1;
    if (b)
    {
      val |= 0x0000001;
    }
    else
    {
      val &= 0xFFFFFFFE;
    }
    val = htobe32(val);
    return val;
  }

}
