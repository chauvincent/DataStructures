// Program 1 - Kevin Chan && Vincent Chau
#include "LongInt.h"

static LongInt sum;

LongInt& LongInt::operator+ (LongInt &rhs)
{

  int num = 0;
  
  ListItr<char> i = listNum.first(); 
  
  ListItr<char> i2 = rhs.listNum.first();
  
  ListItr<char> i3 = sum.listNum.zeroth();

  int carry = 0, a = 0 ,b = 0;

  while(!i2.isPastEnd() && !i.isPastEnd())
  {
    a = i.retrieve();
    
    i.advance();
    
    b = i2.retrieve();
    
    i2.advance();
    
    num = num + a + b;
    
    if(num >= 10)
    {
    
      carry = num % 10;
      
      sum.listNum.insert(carry, i3);
      
      num = num / 10; 
    
    }
    else
    {
      sum.listNum.insert(num, i3); 
      
      num = num / 10; 
    }

    i3.advance();
  
  }

  if(i2.isPastEnd())
  {
  
    while(!i.isPastEnd())
    {
  
      a = i.retrieve();
  
      i.advance();
  
      num = num + a;
  
      if(num>=10)
      {
  
        carry = num % 10;
  
        sum.listNum.insert(carry, i3);
  
        num = num / 10;
  
      }
      else
      {
  
        sum.listNum.insert(num, i3);
  
        num = num / 10;
  
      }
  
      i3.advance();
  
    }
  }
  
  else
  {

    while(!i2.isPastEnd())
    {
    
      b = i2.retrieve();
    
      i2.advance();
    
      num = num + b;
    
      if(num>=10)
      {
    
        carry = num % 10;
    
        sum.listNum.insert(carry % 10, i3);
    
        num = num / 10;
    
      }
      else
      {
    
        sum.listNum.insert(num, i3);
    
        num = num / 10;
    
      }
    
      i3.advance();
   
    }
  }

  return sum;
} 

LongInt& LongInt::operator= (LongInt &rhs)
{
 
  ListItr <char> i = listNum.zeroth(); 

  ListItr <char> i2 = rhs.listNum.first();

  while(!i2.isPastEnd())
  {
  
    sum.listNum.insert(i2.retrieve(), i);

    i.advance();

    i2.advance();
  
  }

  return sum;

}
