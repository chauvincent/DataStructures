// Author: Vincent Chau && Kevin Chan
// ECS 60
// Program 4 familytree.cpp
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "familytree.h"
using namespace std;

FamilyTree::FamilyTree(Family *families, int familyCount) : hashTable(familyCount * 3)
{

	int pid1, pid2;

	for(int i = 0; i < familyCount; i++)
  	{
    	pid1 = hashTable.find(families[i].person);
    
    	if(families[i].spouse.year != -1)
      
      		pid2 = hashTable.find(families[i].spouse);
    
    	else
      		
      		pid2 = -1;
    
    	for(int j = 0; j < families[i].childCount; j++)
    	{
      		int child = hashTable.find(families[i].children[j]);
      
      		hashTable.array[child].pid1 = pid1;
      
      		hashTable.array[child].pid2 = pid2;
    	} 

    }  

} // FamilyTree()

int YearIndexCmp(const void *ptr1, const void *ptr2)
{
	int diff = ((YearIndex*)ptr2)->year - ((YearIndex*)ptr1)->year;
	
	if(diff != 0)

    	return diff;
  
  return ((YearIndex*)ptr2)->index - ((YearIndex*)ptr1)->index;

}

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{

  	for(int i = 0; i < queryCount; i++)
  	{

		front = back = front2 = back2 = 0;
 
 		int personID = hashTable.find(queries[i].person1);
 		
 		// enqueue first query
 		Queue1[back].index = personID;
    
    	Queue1[back].year = hashTable.array[personID].person.year;
    
    	back++;
    
    	while(back != front)
    	{
      		// enqueue parents of person1
      		if(hashTable.array[Queue1[front].index].pid1 >= 0)
      		{
        		
        		int parent1 = hashTable.array[Queue1[front].index].pid1;
        		
        		Queue1[back].index = parent1;
       
       			Queue1[back].year = hashTable.array[parent1].person.year;
        
        		back++;
      		
      		} 
      
      		if(hashTable.array[Queue1[front].index].pid2 >= 0)
      		{
        		int parent2 = hashTable.array[Queue1[front].index].pid2;
        		
        		Queue1[back].index = parent2;
        
        		Queue1[back].year = hashTable.array[parent2].person.year;
        
        		back++;
      		}  
      		
      		front++;
    	} 

    	// for query two
    	int personID2 = hashTable.find(queries[i].person2);
    
    	Queue2[back2].index = personID2;
    
    	Queue2[back2].year = hashTable.array[personID2].person.year;
    
    	back2++;
    
    	while(back2 != front2)
    	{
      		// enqueue parents of person1
      		if(hashTable.array[Queue2[front2].index].pid1 >= 0)
      		{
        		int parent1 = hashTable.array[Queue2[front2].index].pid1;

        		Queue2[back2].index = parent1;
        
        		Queue2[back2].year = hashTable.array[parent1].person.year;
        
        		back2++;

      		}  
      
      		if(hashTable.array[Queue2[front2].index].pid2 >= 0)
      		{
        		int parent2 = hashTable.array[Queue2[front2].index].pid2;

        		Queue2[back2].index = parent2;
        
        		Queue2[back2].year = hashTable.array[parent2].person.year;
        
        		back2++;
      		}
      
      front2++;

    } 
    	// sort the ancestor queues by year
    	qsort(Queue1, back, sizeof(YearIndex), YearIndexCmp);

    	qsort(Queue2, back2, sizeof(YearIndex), YearIndexCmp);
    
    	j = j2 = 0;
    
    	// pop off queues and compare ancestors
    	while(j < back && j2 < back2)
    	{
     		if(Queue1[j].year > Queue2[j2].year)
    			j++;
      
     		else
        
        		if(Queue1[j].year < Queue2[j2].year)
         			j2++;
        
        		else  
        
          			if(Queue1[j].index > Queue2[j2].index)
            			j++;
        
          			else
        
            		if(Queue1[j].index < Queue2[j2].index)
              			j2++;
            		else
            		{
            	
            			memcpy(&answers[i], &hashTable.array[Queue1[j].index].person, sizeof(Person));
            	
            			break;
            		} 
   		} 


    	if(j == back || j2 == back2)
      		answers[i].year = -1;

  	}

}  


