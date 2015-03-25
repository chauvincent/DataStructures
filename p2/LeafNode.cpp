#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;

LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


LeafNode* LeafNode::remove(int value)
{   // To be written by students
  int pos = 0;

  int halfSize = (leafSize+1)/2;
  // find the value of position
  while(pos < count)
  {
    if(values[pos] == value);
      break; // break if found
    pos++;
  }
  
  // if found, shift array left
  if(pos < count)
  {
      --count;
      int index = pos;

      while(index < count)
      {
        values[index] = values[index+1];
        index++;
      }

      // if num of value < leafsize+1 / 2 then
      // look left, look right

      if(count < halfSize)
      {
          if(leftSibling != NULL)
              return removeWithLeftSibling();
          else
            if(rightSibling!=NULL)
              return removeWithRightSibling(pos);

      }

      // if position is the 1st element and parent is not null
      if(!pos && parent != NULL)
      {
        parent->resetMinimum(this);
      }      
 
  }

  return NULL;  // filler for stub
}


LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()


LeafNode* LeafNode::removeWithLeftSibling()
{
    int halfSize = (leafSize + 1) / 2, first = values[0];
  
    //check if we can borrow from left
    if(leftSibling->getCount() > halfSize)
    {
        // insert largest value from left sibling
        insert(leftSibling->getMaximum());
        
        leftSibling->remove(first);

        // if parent is not null, reset min
        if(parent != NULL)
        {
          parent->resetMinimum(this);
        }

        return NULL;
    }
    else 
    {
      // cant borrow, must merge
      // insert all elements of current node into left sibling
      // then set right sibling

      for(int i = 0; i < count; i++)
        leftSibling->insert(values[i]);

      leftSibling->setRightSibling(rightSibling);

      if(rightSibling != NULL)
        rightSibling->setLeftSibling(leftSibling);

      return this;

    }
} // removeWithLeftSibling()


LeafNode* LeafNode::removeWithRightSibling(int pos)
{
    int halfSize = (leafSize + 1)/2;
    //check if we can borrow from right

    if(rightSibling->getCount() > halfSize)
    {
        //insert min from right
        insert(rightSibling->getMinimum());
        
        rightSibling->remove(values[count-1]);

        // if parent is not null, resetmin
        if(pos == 0)
            parent->resetMinimum(this);
        
          return NULL;
    }
    else 
    { // must merge
      // If we cant borrow from left
      // Insert largest value from left
      for(int i = 0; i < count; i++)
        rightSibling->insert(values[i]);

      rightSibling->setLeftSibling(leftSibling);

      if(leftSibling != NULL)
          leftSibling->setRightSibling(rightSibling);

        return this;
    }

} 

