#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}


double ImageTraversal::calculateDeltaPublic(const HSLAPixel & p1, const HSLAPixel & p2){
  return calculateDelta(p1, p2);
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {

}
ImageTraversal::Iterator::Iterator(const PNG &png, double tolerance, const Point &start, bool checkDFS) {
  this->png = png;
  this->checkDFS = checkDFS;
  this->tolerance = tolerance;
  this->start = start;
  visitedPoints = vector<vector<bool>>(png.width(), vector<bool>(png.height()));
  for(unsigned i = 0; i < png.width(); i++){
    for(unsigned j = 0; j < png.height(); j++){
        visitedPoints[i][j] = false;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // if(point.x < png.width() && point.y < png.height()){
  //   if(calculateDeltaPublic(*png.getPixel(point.x,point.y),*png.getPixel(prev.x, prev.y)) < tolerance){
  //   s.push(point);
  //   prev = point;
  //   }
  // }
  // else
  //   return;
  //   add(Point(point.x+1, point.y));
  //   add(Point(point.x, point.y+1));
  //   add(Point(point.x-1, point.y));
  //   add(Point(point.x, point.y-1));
  if(checkDFS == 1){
    DFS pls = newDFS();
    pls.begin();

  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return Point(0, 0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if () {
    /* code */
  }
  else
    return false;
}
