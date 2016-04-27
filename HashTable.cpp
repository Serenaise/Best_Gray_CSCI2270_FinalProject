#include "HashTable.h"
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <fstream>
#include "Debug.h"

using namespace std;

HashTable::HashTable(int _size)
{
  //ctor
  tableSize = _size;
  collisions = 0;
  hashTable = new HashElem*[tableSize];
  //hashTable = new HashElem*[tableSize];
  //initToNull();
  for(int i = 0; i < _size; i++){
    hashTable[i] = NULL;
  }
}
HashTable::~HashTable()
{
  delete hashTable;
  //dtor
}
int HashTable::getCollisions()
{
  return collisions;
}
//added hashTable declaration here, still needs to delete each element of array
void HashTable::initToNull()
{
  hashTable = new HashElem*[tableSize];
  for(int x = 0; x < tableSize; x++)
  {
    if(hashTable[x] != NULL){
      HashElem* current = hashTable[x];
      while(current->next != NULL){
        current = current->next;
        delete current->previous;
      }
      delete current;
      hashTable[x] = NULL;
    }
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
    collisions+=1;
    current = hashTable[index];
    while (current -> next != NULL)
    {
      current = current -> next;
    }
    current -> next = elk;
    elk -> previous = current;
  }
}
void HashTable::insertRandSum(std::string name)
{
  int index = hashRandSum(name, tableSize);
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
    collisions+=1;
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
int HashTable::hashRandSum(std::string str, int sz)
{
  int sum = 0;
  int Rand = 0;
  for (int i = 0; i < str.size(); i++)
  {
    srand(Rand + str[i]);
    sum = rand();
  }
  cout << sum << endl;
  sum = sum % sz;
  return sum;
}
/*This DOES NOT break.  Don't do anything to it!*/
/*Note:If you need to comment this function out PLEASE PLEASE PLEASE use preprocessor directives.  That is, if0 and endif */
void HashTable::SHA1(string message, uint32_t hh[5])
{
  //SHA1("")
  //gives hexadecimal: da39a3ee5e6b4b0d3255bfef95601890afd80709
  {
    union {
      uint64_t Int64;
      char Chars[sizeof(uint64_t)];
    } var;
    //unsigned 32 bit nothing up my sleave ints
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;
    //The message length in bits. Stored as host endian
    uint64_t ml = (message.length())*8;
    //Append the bit '1' to the message
    message.push_back(0x80);
    //Append '0' until the message length mod 512 is 448
    while ((message.length()*8)%512 != 448)
    {
      //cout << "Before: " << message.length() << endl;
      message.push_back(0x00);
      //cout << "After: " << message.length() << endl;
    }
    //Convert message length from host to big endian
    //ml = htobe64(ml);
    //Append the original message size to the end of the message
    var.Int64 = htobe64(ml);
    for(int i = 0; i < sizeof(uint64_t); ++i)
    {
      //Push in big endian order
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
        //cout << (int)ChunkV[CI][ci] << endl;
      }
    }
    for(int x = 0; x < ChunkV.size(); ++x)
    {
      uint32_t w[80];
      //uint32_t *wordptr;
      //wordptr = (uint32_t*)&ChunkV[x][0];
      //w[i] = *wordptr;
      for(int i = 0,j = 0; i < 64; i += 4, j++)
      {
        w[j] = 0;
        w[j] = ((uint32_t)ChunkV[x][i]) << 24 | ((uint32_t)ChunkV[x][i + 1]) << 16 | ((uint32_t)ChunkV[x][i + 2]) << 8 | ((uint32_t)ChunkV[x][i + 3]);
        //w[j] = htobe32(w[j]);
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
        if (0 <= i && i <= 19)
        {
          f = (b & c) | ((~b) & d);
          k = 0x5A827999;
        }
        else if (20 <= i && i <= 39)
        {
          f = b ^ c ^ d;
          k = 0x6ED9EBA1;
        }
        else if (40 <= i && i <= 59)
        {
          f = (b & c) | (b & d) | (c & d);
          k = 0x8F1BBCDC;
        }
        else if (60 <= i && i <= 79)
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
      }
      h0 = h0 + a;
      h1 = h1 + b;
      h2 = h2 + c;
      h3 = h3 + d;
      h4 = h4 + e;
    }
    //hh[5];
    hh[0] = htobe32(h0);
    hh[1] = htobe32(h1);
    hh[2] = htobe32(h2);
    hh[3] = htobe32(h3);
    hh[4] = htobe32(h4);
    /*hh[0] = h0;
    hh[1] = h1;
    hh[2] = h2;
    hh[3] = h3;
    hh[4] = h4;*/
    printf("hh (as uint8_t):\n");
    HexDump(stdout, (uint8_t *) hh, 20);/*from Debug.h should be taken out at some point*/
    printf("\n");
  }
}
/*Also works fine*/
uint32_t HashTable::leftRotate(uint32_t val, int itt)
{
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
  }
  return val;
}

int HashTable::hashScrabble(std::string str, int sz){
  int sum = 0;
  for(int i = 0; i < str.size(); i++){
    char c = tolower(str[i]);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
        || c == 'l' || c == 'n' || c == 's' || c == 'r'){
          sum+=1;
        }
    else if(c == 'd' || c == 'g'){
      sum += 2;
    }
    else if(c == 'b' || c == 'c' || c == 'm' || c == 'p'){
      sum += 3;
    }
    else if(c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y'){
      sum += 4;
    }
    else if(c == 'k'){
      sum += 5;
    }
    else if(c == 'j' || c == 'x'){
      sum += 8;
    }
    else if(c == 'q' || c == 'z'){
      sum += 10;
    }
  }
  sum = sum % tableSize;
  return sum;
}

void HashTable::insertScrabble(string name)
{
  cout << name << endl;
  int index = hashScrabble(name, tableSize);
  HashElem *current;
  HashElem *elk = new HashElem(name);
  if (hashTable[index] == NULL)
  {
    hashTable[index] = elk;
    cout <<" Null thing" <<  hashTable[index]->title << endl;
  }
  else
  {
    cout << "here" << hashTable[index]->title << endl;
    collisions += 1;
    current = hashTable[index];
    while (current -> next != NULL)
    {
      current = current -> next;
    }
    current -> next = elk;
    elk -> previous = current;
  }
}
