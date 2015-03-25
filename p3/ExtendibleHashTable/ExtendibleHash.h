//Kevin Chan and Vincent Chau
#ifndef EXTENDIBLE_HASH_H
#define EXTENDIBLE_HASH_H

class ExtendibleLeaf
{
    int LeafSize;
    int count;
    int *arr;

    public:

      ExtendibleLeaf(int LSize);
  
      bool checkIfSplit(ExtendibleLeaf ** Directory, int object, int bits); 

      bool split(ExtendibleLeaf ** Directory, int object, int bits);
      
      void insert(int object);
      
      void remove(int object);
      
      int find(int object);
      

  
}; // ExtendibleLeaf


class ExtendibleHash
{
    ExtendibleLeaf   **Directory;

    int bits;

    int size;

    int LeafSize;

    int notfound;

    public:
      
      void doubleSize(const int &object);

      friend class ExtendibleLeaf; // get rid of non-ref error
      
      ExtendibleHash(const int & notFound, int s, int LSize = 2);
      
      void insert(const int &object); 
      
      void remove(const int &object);
      
      const int &find(const int &object);

      int GetBits()const {return bits;}

}; // class ExtendibleHashing

#include "ExtendibleHash.cpp"
#endif