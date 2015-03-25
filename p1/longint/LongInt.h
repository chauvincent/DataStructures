#ifndef LongIntH
#define LongIntH
#include <iostream>
#include "StackLi.h"
#include "LinkedList.h"

using namespace std;

class LongInt 
{
	
	public:

    LongInt(){listNum.makeEmpty();};

  	LongInt& operator+ (LongInt &rhs);
  	
  	LongInt& operator= (LongInt &rhs);

	  friend istream& operator>> (istream &input, LongInt &rhs)
    {  

        char let;

        input >> let;

        rhs.listNum.insert(let - 48, rhs.listNum.zeroth());

      do
      {

          input >> let;

          rhs.listNum.insert(let - 48, rhs.listNum.zeroth());

          let = input.peek();

      }
      while(isdigit(let));

      return input;

    } 
  	
    friend ostream& operator<< (ostream &output, LongInt &rhs)
    {
  
        StackLi<int> tempStack;
    
        ListItr<char> i = rhs.listNum.first();

        while(!i.isPastEnd())
        {

          int val = (int)(i.retrieve());

          tempStack.push(val);

          i.advance();

        }


        while(!tempStack.isEmpty())
        {
          output << tempStack.top();

          tempStack.pop();
        }

        return output;

    } 

  private:
    
  	List <char> listNum;
};



#endif
