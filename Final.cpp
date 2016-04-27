#include <iostream>
#include "HashTable.h"
#include "stdlib.h"
#include <fstream>
#include <sstream>
#include "Debug.h"
#include <stdio.h>

using namespace std;

int DEFAULT_TABLESIZE = 10;
int menu();
int HashMenu();

int main()
{
  int C, year;
  bool quit = false;
  HashTable h = HashTable(DEFAULT_TABLESIZE);
  cout << "declared table" << endl;
  string title;
  int hash = 1;
  //h.initToNull();
  while (!quit)
  {
    C = 0;
    try{
      C = menu();
    }
    catch(const char* msg){
      cerr << msg << endl;
    }
    if (C == 1)
    {
      int choice = 0;
      bool entered = false;
      while(!entered){
        cout << "Choose whether to input a file or a single input" << endl;
        cout << "1. Single input" << endl;
        cout << "2. Enter file" << endl;
        cin >> choice;
        if(choice == 1){
          cout << "Enter title:" << endl;

          cin.ignore();
          getline(cin, title);
          if(hash == 1){
            h.insertSum(title);
          }
          else if(hash == 2){
            h.insertMul(title);
          }
          else if(hash == 3){
            h.insertRandSum(title);
          }
          else if(hash == 4){
            h.insertScrabble(title);
          }
          else{
			uint32_t res[5];
            h.SHA1(title,res);
            printf("%08x%08x%08x%08x%08x\n",res[0], res[1], res[2], res[3], res[4]);
            /*cout << hex << res[0] << hex << res[1] << hex << res[2] << hex << res[3] << hex << res[4] << endl;
             // LCB: Debug.
         printf("res (as uint8_t):\n");
         HexDump(stdout, (uint8_t *) res, 20);
         printf("\n");*/
          }
          //uint32_t res[5];
          //h.insertSum(title); //Not thoroughly tested, but it seems to work..
          //h.SHA1(title,res);
          //cout << hex << res[0] << hex << res[1] << hex << res[2] << hex << res[3] << hex << res[4] << endl;
          cout << "Number of collisions: " << h.getCollisions() << endl;
          entered = true;
        }
        else if(choice == 2){
          //insert code to read in file here
          string filename;
          cout << "Please input the name of the file" << endl;
          cin >> filename;
          if (FILE *file = fopen(filename.c_str(), "r")) {
            cin.ignore();
            string word;
            ifstream fin(filename.c_str());
            while(fin >> word){
              //h.insertScrabble(word);
              if(hash == 1){
                h.insertSum(word);
              }
              else if(hash == 2){
                h.insertMul(word);
              }
              else if(hash == 3){
                h.insertRandSum(word);
              }
              else if(hash == 4){
                h.insertScrabble(word);
              }
              else{
                uint32_t array[5];
                h.SHA1(word, array);
              }
            }
            fclose(file);
            cout << "Number of collisions:" << h.getCollisions() << endl;
            entered = true;
          }
          else {
            cout << "Bad file name" << endl;
            entered = true;
          }
        }
        else{
          cout << "Invalid input, please try again" << endl;
          cin.clear();
          while (cin.get() != '\n') ;
        }
      }
    }
    else if (C == 2)
    {
      cout << "Enter title:" << endl;
      cin.ignore();
      getline(cin, title);
      if(hash == 1){
        h.deleteSum(title);
      }
      else if(hash == 2){
        h.deleteMul(title);
      }
      else if(hash == 3){
        h.deleteRandSum(title);
      }
      else if(hash == 4){
        h.deleteScrabble(title);
      }
      else{
        cout << "You cannot delete from SHA1" << endl;
      }
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
      cout << "This will delete everything in the array" << endl;/*Might want to add option to bail on changing tableSize*/
      cout << "Please enter a new table size:" << endl;
      cin.ignore();
      getline(cin, newsize);
      /*I changed this next comand from stoi becuase that doesn't work on my computer.
      Make sure the string is a valid integer.  Add end pointer (instead of NULL) to make sure that the whole string was used in conversion.
      To force to be base 10 make the last argument 10*/
      h.setTableSize(strtol(newsize.c_str(),NULL,0));
    }
    else if (C == 6){
      cout << "Choose a new hash function.  This will remove everything from the current array" << endl;
      hash = HashMenu();
    }
    else if (C == 7)
    {
      quit = true;
      cout << "Goodbye!" << endl;
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
  cout << "6. Change hash function" << endl;
  cout << "7. Quit" << endl;
  //cin >> choice;
  if(cin >> choice && choice <= 7 && choice > 0){
  return choice;
}
else{
  cout << "Not a valid input.  Please input the number next to the menu item you wish to select" << endl;
  cin.clear();
  while (cin.get() != '\n') ;
}

  //return choice;
}

int HashMenu()
{
  int choice;
  cout << "======Hash Menu======" << endl;
  cout << "1. Sum" << endl;
  cout << "2. Multiplication" << endl;
  cout << "3. Random" << endl;
  cout << "4. Scrabble" << endl;
  cout << "5. SHA1 (note: this will not create a hash table)" << endl;
  cout << "6. Quit" << endl;
  //cin >> choice;
  if(cin >> choice && choice <= 6 && choice > 0){
  return choice;
}
else{
  cout << "Not a valid input.  Please input the number next to the menu item you wish to select" << endl;
  cin.clear();
  while (cin.get() != '\n') ;
}

  //return choice;
}
