//Kevin Chan and Vincent Chau
#include "ExtendibleHash.h"

const int NOT_FOUND = 0;

inline int Ehash(int n, int bits){ return (n >> (18 - bits));};

inline int shla(int n, int p) {	return n<<p; }

bool ExtendibleLeaf::checkIfSplit(ExtendibleLeaf ** Directory, int object, int bits)
{
	if(count < LeafSize) // if dont need to split
	{
		arr[count++] = object;
		return false;
	}

	return split(Directory, object, bits);

}
ExtendibleLeaf::ExtendibleLeaf(int LSize)
{
	arr = new int[LSize];

	count = 0;

	LeafSize = LSize;
}

int ExtendibleLeaf::find(int object)
{
	for(int i = 0; i < count; i++)
		if(arr[i] == object)
			return object;

	return -1; 
}

void ExtendibleLeaf::insert(int object)
{
	arr[count++] = object;
}

void ExtendibleLeaf::remove(int object)
{

	for(int i = 0; i < count; i++)
		if(arr[i] == object)  // search
		{
			int k = i;
	
			while(k < this->count-1) 
			{
				this->arr[k] = this->arr[k+1];
				k++;
			}

			this->arr[count-1] = 0;
		
			--(this->count);
		
			break; // found && removed
		}

}

bool ExtendibleLeaf::split(ExtendibleLeaf ** Directory, int object, int bits) //pointer to new leaf
{
	int pos = Ehash(object,bits), i = 0;

	while( i < count)
	{
		if(Ehash(arr[i],bits) != pos) //found a value to split
		{
			int nPos = Ehash(arr[i],bits);
			
			Directory[nPos] = new ExtendibleLeaf(LeafSize);
			
			Directory[nPos]->insert(arr[i]); 
		
			int k = i;
	
			while(k < this->count-1) 
			{
				this->arr[k] = this->arr[k+1];
				
				k++;
			}

			this->arr[count-1] = 0;
			
			--(this->count);
	
			for(int j = i; j < count; j++) 
			{
				if(Ehash(arr[j],bits) == nPos)
				{
					Directory[nPos]->insert(arr[j]); 

					int k = j;
	
					while(k < this->count-1) 
					{
						this->arr[k] = this->arr[k+1];

						k++;
					}

					this->arr[count-1] = 0;

					--(this->count);

					j--; 
				}
			}

			insert(object);

			return false; 
		}
		i++;
	} // endwhile

	return true;

}


ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) :
	bits(b), LeafSize(LSize)
{
	int pos = shla(1, b);

	Directory = new ExtendibleLeaf* [pos];

	for(int i = 0; i < pos; i++)  // point to empty leaf
		Directory[i] = new ExtendibleLeaf(LSize);

	notfound = notFound;

} // ExtendibleHash()

void ExtendibleHash::insert(const int &object)
{
	if(Directory[Ehash(object,bits)]->checkIfSplit(Directory, object, bits))
		doubleSize(object);

} // insert()

void ExtendibleHash::remove(const int &object)
{

	Directory[Ehash(object,bits)]->remove(object);

}  // remove()


const int &ExtendibleHash::find(const int &object)
{
	const int &p = Directory[Ehash(object, bits)]->find(object);

	return  (p);

}  // find()


void ExtendibleHash::doubleSize(const int &object)
{

	int nPos = shla(1, bits+1);

	ExtendibleLeaf **tempDirectory = new ExtendibleLeaf* [nPos];

	int k = 0, pos = shla(1, bits);

	while(k < pos) // double size
	{  
		tempDirectory[2*k] = Directory[k]; 
		
		tempDirectory[2*k+1] = Directory[k];

		k++;
	}

	Directory = tempDirectory;
	
	bits++;

	if(Directory[Ehash(object,bits)]->checkIfSplit(Directory, object, bits))
		doubleSize(object); //if cant, double size
 
}  // doubleSize()


