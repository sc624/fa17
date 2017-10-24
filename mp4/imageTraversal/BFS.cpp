
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
  this->png = png;
  this->start = start;
  this->tolerance = tolerance;

  visitedPoints = vector<vector<bool>>(png.width(), vector<bool>(png.height()));
  for(unsigned i = 0; i < png.width(); i++) {
    for(unsigned j = 0; j < png.height(); j++) {
      visitedPoints[i][j] = false;
    }
  }

  add(start);
  while (q.empty() == false) {
    pop();
  }
    for(unsigned i = 0; i < png.width(); i++) {
      for(unsigned j = 0; j < png.height(); j++) {
        visitedPoints[i][j] = false;
      }
    }
  while (q.empty() == false) {
    q.pop();
  }
  add(start);
  iteratorEnd = visitedPath.end();
  visitedPath.clear();
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, visitedPath.begin(), iteratorEnd);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, iteratorEnd, iteratorEnd);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel point1 = *(png.getPixel(point.x,point.y));
  HSLAPixel point2 = *(png.getPixel(this->start.x,this->start.y));  //check here
  bool toleranceCheck;
  if(calculateDeltaPublic(point1,point2) < tolerance)
    toleranceCheck = true;
  else
    toleranceCheck = false;

  bool notVisited = !visitedPoints[point.x][point.y];
  if(toleranceCheck && notVisited)
    q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(!q.empty()) {
     Point point = q.front();
     if(!visitedPoints[point.x][point.y]) {
       visitedPath.push_back(point);
       q.pop();
       visitedPoints[point.x][point.y] = true;

      if(point.x+1 < png.width())
        add(Point(point.x+1, point.y));
      if(point.y+1 < png.height())
        add(Point(point.x, point.y+1));
      if(point.x >= 1)
        add(Point(point.x-1, point.y));
      if(point.y >= 1)
        add(Point(point.x, point.y-1));

       return point;
     }
     else
       q.pop();
   }
   return Point(png.width(), png.height());
 }

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}
