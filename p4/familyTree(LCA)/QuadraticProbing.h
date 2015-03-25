#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include "familyRunner.h"

class Person2
{
  public:
  
    Person person;
  
    int pid1;
  
    int pid2;
}; // keep track for queue

class QuadraticHashTable
{
  public:
    explicit QuadraticHashTable(int size);
    int find(Person &x);
    Person2 *array;
    int currentSize;
};

#endif
