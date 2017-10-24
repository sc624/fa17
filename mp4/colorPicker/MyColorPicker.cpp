#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
 MyColorPicker::MyColorPicker(HSLAPixel color) : color(color) { }

 HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
   return color;
}
