#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
#include <stdint.h>

struct HashElem{
	std::string title;
	HashElem *next;
  HashElem *previous;

	HashElem(){};
	HashElem(std::string in_title)
	{
		title = in_title;
		next = NULL;
		previous = NULL;
	}

};

class HashTable
{
	public:
		HashTable(int _size);
		~HashTable();
		void printTableContents();
		void initToNull();/*Needs work. Should be made to delete everything in the hash table.*/
		int getCollisions();
		void insertSum(std::string name);
		void insertMul(std::string name);
		void insertRandSum(std::string name);
		void insertScrabble(std::string);
		void SHA1(std::string name, uint32_t hh[5]);
		void deleteSum(std::string name);
		void deleteMul(std::string name);
		void deleteRandSum(std::string name);
		void deleteScrabble(std::string name);
		void findSum(std::string name);
		void findMul(std::string name);
		void findRandSum(std::string name);
		void findScrabble(std::string name);
		void setTableSize(int newsize);//added function so user can set table size
	private:
		int hashSum(std::string x, int s);
		int hashMultiply(std::string k, int sz);
		int hashRandSum(std::string str, int sz);
		int hashScrabble(std::string str, int sz);
		uint32_t leftRotate(uint32_t val, int itt);
		//int SHA1(std::string name);/*This one only needs the name and it returns a hexidecimal.*/
		int tableSize;
		int collisions;
		HashElem* *hashTable;

};

#endif // HASHTABLE_H
