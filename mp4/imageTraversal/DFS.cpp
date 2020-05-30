#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
	picture = new PNG;
	*picture = png;
	tol = tolerance;
	PointsToVist.push(start);
	CurrPoint = start;
	bool** array = new bool*[png.width()];
	for(int i=0;i<(int)png.width();i++){
		array[i]=new bool[png.height()];
		for(int j=0;j<(int)png.height();j++){
			array[i][j]=false;
		}
	}
	Seen = array;
	Seen[start.x][start.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
	ImageTraversal::Iterator MyIt(this->pop(), this);
	return MyIt;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
	Point ImpossiblePoint(picture->width()+1,picture->height());
	ImageTraversal::Iterator it(ImpossiblePoint, this);
	return it;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
	if( ! Seen[point.x][point.y] ){
		PointsToVist.push(point);
		Seen[point.x][point.y] = true;
	}else{return;}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
	Point retpoint;
	if(PointsToVist.empty() ){
		retpoint.x = picture->width()+1;
		retpoint.y = picture->height();
		CurrPoint = retpoint;
		return retpoint;
	}
	retpoint = PointsToVist.top();
	PointsToVist.pop();
	if(retpoint.x+1 <picture->width() && calculateDelta(*picture->getPixel(retpoint.x,retpoint.y), *picture->getPixel(retpoint.x+1,retpoint.y) ) <= tol ){
		retpoint.x++;
		add(retpoint);
		retpoint.x--;
	}
	if(retpoint.y+1 <picture->width() && calculateDelta(*picture->getPixel(retpoint.x,retpoint.y), *picture->getPixel(retpoint.x,retpoint.y+1) ) <= tol ){
		retpoint.y++;
		add(retpoint);
		retpoint.y--;
	}
	if(retpoint.x-1 <picture->width() && retpoint.x > 0 && calculateDelta(*picture->getPixel(retpoint.x,retpoint.y), *picture->getPixel(retpoint.x-1,retpoint.y) ) <= tol ){
		retpoint.x--;
		add(retpoint);
		retpoint.x++;
	}
	if(retpoint.y-1 <picture->width() && retpoint.y > 0 && calculateDelta(*picture->getPixel(retpoint.x,retpoint.y), *picture->getPixel(retpoint.x,retpoint.y-1) ) <= tol ){
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
Point DFS::peek() const {
  /** @todo [Part 1] */
  return CurrPoint; 
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return PointsToVist.empty();
}
