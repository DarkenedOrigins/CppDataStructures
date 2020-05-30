#include "Hash.h"
#include <string>
#include<algorithm>

unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	//Your code here
	for(auto it=str.begin(); it<str.end(); it++){
		b_hash *= 33; 
		b_hash += (unsigned long)*it;
	}
	unsigned long retval=b_hash%M;
	return retval;
}

std::string reverse(std::string str)
{
    std::string output = "";
	//Your code here
	for(int i=str.size()-1;i>=0;i--){
		output.push_back(str[i]);
	}
	return output;
}
