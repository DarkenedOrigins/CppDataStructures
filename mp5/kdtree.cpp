#include <algorithm>
#include <cmath>
/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if(first[curDim] < second[curDim]){
		return true;
	}
	if(first[curDim] > second[curDim]){
		return false;
	}
	return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	double CurrDistance = 0;
	double NewDistace = 0;
	for(int i=0; i<Dim;i++){
		CurrDistance += std::pow(target[i]-currentBest[i], 2);
		NewDistace += std::pow(target[i]-potential[i], 2);
	}
	if(CurrDistance == NewDistace){
		return potential < currentBest;
	}
	return NewDistace < CurrDistance;
}

template<int Dim>
int KDTree<Dim>::Partition(int first, int last, int mid_index, int CurDim){
	Point<Dim> mid = points[mid_index];
	std::swap(points[last],points[mid_index]);
	int Index = first;
	for(int i=first; i<last; i++){
		if( smallerDimVal(points[i],mid,CurDim) || points[i] == mid ){
			std::swap(points[Index], points[i] );
			Index++;
		}
	}
	std::swap(points[last], points[Index]);
	return Index;
}

template <int Dim>
void KDTree<Dim>::QuickSelect(int first, int last, int k, int CurDim){
	int median = Partition(first, last, k, CurDim);
	if(median == k){
		return;
	}
	if(k < median){
		QuickSelect(first,median-1,k,CurDim);
	}else{
		QuickSelect(median+1,last,k,CurDim);
	}
	return;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	if(newPoints.size() == 0) return;
	points = newPoints;
	int first = 0;
	int last = newPoints.size()-1;
	int CurDim = 0;
	while(first != last){
		int median = (first + last)/2;
		QuickSelect(first, last, median, CurDim);
		CurDim = (CurDim+1)%Dim;
		if(first < median){
			last = median-1;
		}
		if(last > median){
			first = median+1;
		}
	}
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return NearestNeighborHelper(0, query, 0, points.size()-1, points[(points.size()-1)/2] );
}

template <int Dim>
Point<Dim> KDTree<Dim>::NearestNeighborHelper(int CurDim, const Point<Dim> &query, int first, int last, const Point<Dim> &CurBest) const{
	Point<Dim> retval = CurBest;
	bool TargetLeft = true;
	if(first == last){
		//at leaf
		if(shouldReplace(query, CurBest, points[first]) ){
			retval = points[first];
			return retval;
		}
		return CurBest;
	}
	int median = (first+last)/2;
	int InnerMedian = 0;
	if(smallerDimVal(points[median], query, CurDim) && last > median){
		retval = NearestNeighborHelper( (CurDim+1)%Dim, query, median+1, last, CurBest);
		TargetLeft = false;
		InnerMedian = (first+median-1)/2;
	}
	if(smallerDimVal(query, points[median], CurDim) && first < median){
		retval = NearestNeighborHelper( (CurDim+1)%Dim, query, first, median-1, CurBest);
		TargetLeft = true;
		InnerMedian = (median+1+last-1)/2;
	}
	//Is current node closer check
	if( shouldReplace(query, retval, points[median] ) ){
		retval = points[median];
	}
	//check the other subtree
	Point<Dim> CurPoint = points[median];
	double distance =0;
	for(int i=0; i<Dim; i++){
		distance += std::pow(query[i]-retval[i],2);
	}
	if( std::pow( CurPoint[CurDim]-query[CurDim], 2) <= distance){
		if(TargetLeft && last > median){
			retval = NearestNeighborHelper( (CurDim+1)%Dim, query, median+1, last, retval);
		}
		if( !TargetLeft && first < median){
			retval = NearestNeighborHelper( (CurDim+1)%Dim, query, first, median-1, retval);
		}
	}
	return retval;
}
