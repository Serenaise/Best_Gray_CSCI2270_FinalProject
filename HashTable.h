#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>

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
		HashTable();
		~HashTable();
		void printTableContents();
		void initToNull();/*Needs work. Should be made to delete everything in the hash table.*/
		int getCollisions();
		void insertSum(std::string name);
		void insertMul(std::string name);
		void insertRandSum(std::string name);
		void insertSHA1(std::string name);/*This is the crypto.  Does not currently work*/
		void deleteSum(std::string name);
		void deleteMul(std::string name);
		void deleteRandSum(std::string name);
		void deleteSHA1(std::string name);
		void find(std::string name);
	private:
		int hashSum(std::string x, int s);
		int hashMultiply(std::string k, int sz);
		int hashRandSum(std::string str, int sz);
		int SHA1(std::string name);/*This one only needs the name and it returns a hexidecimal.*/
		int tableSize;
		int collisions;
		HashElem* hashTable[10];

};

#endif // HASHTABLE_H
