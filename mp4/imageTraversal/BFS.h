#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <unordered_set>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  queue<Point> PointsToVist;
  bool* Seen;
  PNG picture;
  double tol;
  Point CurrPoint;
};

#endif
