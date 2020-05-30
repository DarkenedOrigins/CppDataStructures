#include <vector>
#include <string>
#include "Hash.h"

using namespace std;

int hashFunction(string s, int M) {
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
	int sum = 0;
	for(auto it=s.begin();it<s.end();it++){
		sum += (int)*it;
	}
	return sum%M;
 }

int countCollisions (int M, vector<string> inputs) {
	int collisions = 0;
	// Your Code Here
	vector<int>Same(M,0);
	for(auto it=inputs.begin();it<inputs.end();it++){
		int index = hashFunction(*it,M);
		Same[index]+=1;
	}
	for(auto sit=Same.begin();sit<Same.end();sit++){
		if(*sit >0){	
			collisions += *sit-1;
		}
	}

	return collisions;
}
