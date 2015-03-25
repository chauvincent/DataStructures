#include "QuadraticProbing.h"
#include <cstring>

QuadraticHashTable::QuadraticHashTable(int size) : currentSize(size)
{
  array = new Person2[size];
  
  for(int i = 0; i <size; i++)
    array[i].pid1 = array[i].pid2 = array[i].person.year = -1;
}


int QuadraticHashTable::find(Person &person)
{

  // cut off extras
  int i = strlen(person.firstName);

  memset(&person.firstName[i], 0, 12 - i);

  i = strlen(person.lastName);
  
  memset(&person.lastName[i], 0, 12 - i);

  unsigned int currentPos = 0;

  // fast hash function, via bit shifting
  for(int i = 0; i < 5; i++)
  
    currentPos += person.firstName[i] << person.lastName[i];
 
  currentPos %= currentSize;
  
  if(currentPos < 0)
  
    currentPos += currentSize;

  while(array[currentPos].person.year != -1 && memcmp(&person, &array[currentPos].person, sizeof(Person)))
  {
     if( ++currentPos >= currentSize)
        currentPos = 0;
  }
  
  if(array[ currentPos ].person.year == -1)
    memcpy(&array[currentPos].person, &person, sizeof(Person));
  
  return currentPos;
}


