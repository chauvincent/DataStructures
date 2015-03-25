#ifndef FAMILYTREE_H
#define	FAMILYTREE_H
#include "QuadraticProbing.h"
#include "familyRunner.h"

class YearIndex
{
	public:
  		
  		short year;

		int index;
  
  		YearIndex(short y = 0, int i = 0) : year(y), index(i) {}
}; 

class FamilyTree 
{
	public:

  	YearIndex *Queue1 = new YearIndex[100000];

  	YearIndex *Queue2 = new YearIndex[100000];

  	int front, back, front2, back2, j, j2;

  	QuadraticHashTable hashTable;
	
  	FamilyTree(Family *families, int familyCount);
  
  	void runQueries(Query *queries, Person *answers, int queryCount);

};

#endif	/* FAMILYTREE_H */
