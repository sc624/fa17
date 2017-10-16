#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;
/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  stack<Point> s;
  PNG png;
  Point start;
  Point prev;
  double tolerance;
  vector<Point> visited;
  vector<vector<Point>> 2d;
};

#endif
