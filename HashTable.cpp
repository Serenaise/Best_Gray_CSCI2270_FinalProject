#include "HashTable.h"
#include <iostream>
#include <math.h>

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
/*int HashTable::SHA1(string name)
{
  int h0 = 0x67452301;
  int h1 = 0xEFCDAB89;
  int h2 = 0x98BADCFE;
  int h3 = 0x10325476;
  int h4 = 0xC3D2E1F0;
}*/
