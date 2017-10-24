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
  // unsigned xBoi = start.x;
  // unsigned yBoi = start.y;
  //
  // int pngWidth = png.width();
  // int pngHeight = png.height();
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
    while (!s.empty()) {
      pop();
    }

    for(unsigned i = 0; i < png.width(); i++) {
      for(unsigned j = 0; j < png.height(); j++) {
        visitedPoints[i][j] = false;
      }
    }
    while (s.empty() == false){
      s.pop(); }
    add(start);

    iteratorEnd = visitedPath.end();
    visitedPath.clear();
}




/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */

  return ImageTraversal::Iterator(this, visitedPath.begin(), iteratorEnd);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, iteratorEnd, iteratorEnd);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel point1 = *(png.getPixel(point.x, point.y));
  HSLAPixel point2 = *(png.getPixel(this->start.x, this->start.y));
  bool toleranceCheck;
  if(calculateDeltaPublic(point1,point2) < tolerance)
    toleranceCheck = true;
  else
    toleranceCheck = false;
  bool notVisited = !visitedPoints[point.x][point.y];
  if(toleranceCheck && notVisited)
    s.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::peek() const{
  /** @todo [Part 1] */
return s.top();
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::pop()  {
  /** @todo [Part 1] */
  if(s.empty() == false) {
      Point point = s.top();
      if(visitedPoints[point.x][point.y] == false) {
        visitedPath.push_back(point);
        s.pop();
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
        s.pop();
    }
    return Point(png.width(), png.height());}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */

  return s.empty();
}
