#include <iostream>
#include "HashTable.h"

using namespace std;

int menu();

int main()
{
  int C, year;
  bool quit = false;
  HashTable h;
  string title;
  h.initToNull();
  while (!quit)
  {
    C = menu();
    if (C == 1)
    {
      cout << "Enter title:" << endl;
      cin.ignore();
      getline(cin, title);
      cout << "Enter year:" << endl;
      cin >> year;
      h.insertMul(title,year);
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
    else if (C == 5)
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
  cout << "5. Quit" << endl;
  cin >> choice;
  return choice;
}
