#include <iostream>
#include "HashTable.h"

using namespace std;

int DEFAULT_TABLESIZE = 10;
int menu();

int main()
{
  int C, year;
  bool quit = false;
  HashTable h = HashTable(DEFAULT_TABLESIZE);
  string title;
  //h.initToNull();
  while (!quit)
  {
    C = menu();
    if (C == 1)
    {
      cout << "Enter title:" << endl;
      cin.ignore();
      getline(cin, title);
      h.insertSum(title);  //Changed to insertSum for testing purposes
    }
    else if (C == 2)
    {
      cout << "Enter title:" << endl;
      cin.ignore();
      getline(cin, title);
      h.deleteMul(title);
    }
    else if (C == 3)
    {
      cout << "Enter title:" << endl;
      cin.ignore();
      getline(cin, title);
      h.find(title);
    }
    else if (C == 4)
    {
      h.printTableContents();
    }
    else if (C == 5){
      string newsize;
      cout << "This will delete everything in the array" << endl;
      cout << "Please enter a new table size:" << endl;
      cin.ignore();
      getline(cin, newsize);
      h.setTableSize(stoi(newsize));
    }
    else if (C == 6)
    {
      quit = true;
      cout << "Goodbye!" << endl;
    }
    else
    {
      cout << "Not a valid input" << endl;
    }
  }
  return 0;
}
int menu()
{
  int choice;
  cout << "======Main Menu======" << endl;
  cout << "1. Insert movie" << endl;
  cout << "2. Delete movie" << endl;
  cout << "3. Find movie" << endl;
  cout << "4. Print table contents" << endl;
  cout << "5. Change table size" << endl;
  cout << "6. Quit" << endl;
  cin >> choice;
  return choice;
}
