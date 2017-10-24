#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <queue>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  this->png = new PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  travesties.push(&traversal);
  colorpick.push(&colorPicker);
}


Animation FloodFilledImage::animate(unsigned frameInterval) const {
  return animate(frameInterval);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) {
  Animation animation;
  /** @todo [Part 2] */
  int frame = 0;
  ImageTraversal * traverse;
  ColorPicker * colorp;
  while(travesties.empty() == false){
    ImageTraversal::Iterator it;
    animation.addFrame(*this->png);
    traverse = travesties.front();
    colorp = colorpick.front();

for(it = traverse->begin(); it != traverse->end(); ++it) {
  HSLAPixel pixelColor = colorp->getColor((*it).x, (*it).y);
  HSLAPixel * pixel = this->png->getPixel((*it).x, (*it).y);
  pixel->h = pixelColor.h;
  pixel->s = pixelColor.s;
  pixel->l = pixelColor.l;
  pixel->a = pixelColor.a;
  frame++;
  if(frame % frameInterval == 0) {
    animation.addFrame(*this->png);
  }
}
animation.addFrame(*this->png);
colorpick.pop();
travesties.pop();
}
  return animation;
}
