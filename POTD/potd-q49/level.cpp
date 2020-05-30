#include "MinHeap.h"
#include <math.h>

vector<int> lastLevel(MinHeap & heap)
{
	double NumElements = heap.elements.size() -1;
	int height = (int)log2(NumElements);
	int index = 1;
	for(int i=0;i<height;i++){
		index *= 2;
	}
	vector<int> RetVec;
	for(int i = index; i < (int)heap.elements.size(); i++){
		RetVec.push_back(heap.elements[i]);
	}
	return RetVec;
}

