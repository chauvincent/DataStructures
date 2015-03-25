// Program 1 - Kevin Chan && Vincent Chau
#include <iostream>
#include <vector>

using namespace std;

bool feasible(vector <int> &queens, int &j)
{
	int d;
	
	if(queens[j] == 0 || queens[j] > 8) // if goes off board
	
		return false;
		
	for(int z = 1; z < j; z++)
	{
		
		d = queens[z]-queens[j]; 
		
		if(d == j-z || d == 0 || d == z-j) // P[i] - P[j] != {i-j, 0, j-i})
	
			return false;
		
	}
	
	return true;
}

void backtrack(vector <int> &queens, int &j)
{
	queens[j] = 0; // back track
	
	j--;  
	
	queens[j]++;

}

int main()
{

	vector <int> *queens = new vector<int>;
	 
	queens->resize(9); 
	
	(*queens)[1] = 1; // start at (1,1)
	
	int j = 2; // (next row)
	
	while(j != 9)
	{
		if(feasible(*queens,j))
		{

			j++; // increment queen
		
			if(j > 8) // found solutions to print
			{
				for(int p = 1; p < 8; p++)
					cout << (*queens)[p] << ",";
				
				 
				cout << (*queens)[8];
 
			} //end inner if
		} // end outer if
		else  
		{
			if ((*queens)[j] < 9) 
			{
					(*queens)[j]++; // move queen if we can
			}
			else 
			{
				backtrack(*queens, j);
			} // end if else
		} // end else
	} // end while
	
	delete queens; // free
	
	return 0;

}


