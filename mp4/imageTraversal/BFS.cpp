
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
	picture = png;
	tol = tolerance;
	PointsToVist.push(start);
	CurrPoint = start;
	bool* array = new bool[png.width()*png.height()];
	for(unsigned i=0;i<png.width()*png.height();i++){
		array[i]=false;
	}	
	Seen = array;
	Seen[start.y*png.width()+start.x]= true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
	ImageTraversal::Iterator MyIt(this->pop(), this);
	return MyIt;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
	Point ImpossiblePoint(picture.width()+1,picture.height());
	ImageTraversal::Iterator it(ImpossiblePoint, this);
	return it;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
	if( ! Seen[point.y*picture.width()+point.x]){
		PointsToVist.push(point);
		Seen[point.y*picture.width()+point.x] = true;
	}else{return;}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
	Point retpoint;
	if(PointsToVist.empty() ){
		retpoint.x = picture.width()+1;
		retpoint.y = picture.height();
		CurrPoint = retpoint;
		return retpoint;
	}
	retpoint = PointsToVist.front();
	PointsToVist.pop();
	if(retpoint.x+1 <picture.width() && calculateDelta(*picture.getPixel(retpoint.x,retpoint.y), *picture.getPixel(retpoint.x+1,retpoint.y) ) <= tol ){
		retpoint.x++;
		add(retpoint);
		retpoint.x--;
	}
	if(retpoint.y+1 <picture.width() && calculateDelta(*picture.getPixel(retpoint.x,retpoint.y), *picture.getPixel(retpoint.x,retpoint.y+1) ) <= tol ){
		retpoint.y++;
		add(retpoint);
		retpoint.y--;
	}
	if(retpoint.x-1 <picture.width() && (int)retpoint.x > 0 && calculateDelta(*picture.getPixel(retpoint.x,retpoint.y), *picture.getPixel(retpoint.x-1,retpoint.y) ) <= tol ){
		retpoint.x--;
		add(retpoint);
		retpoint.x++;
	}
	if(retpoint.y-1 <picture.width() && retpoint.y > 0 && calculateDelta(*picture.getPixel(retpoint.x,retpoint.y), *picture.getPixel(retpoint.x,retpoint.y-1) ) <= tol ){
		retpoint.y--;
		add(retpoint);
		retpoint.y++;
	}
	CurrPoint = retpoint;
	return retpoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return CurrPoint;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return PointsToVist.empty();
}
