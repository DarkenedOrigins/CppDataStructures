/* Your code here! */
#ifndef _DISJOINT_SETS_
#define _DISJOINT_SETS_

#include <vector>

class DisjointSets{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion (int a, int b);
	private:
		std::vector<int> set;
};

#endif
