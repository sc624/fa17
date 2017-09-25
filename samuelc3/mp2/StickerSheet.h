#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"
using namespace std;    
class StickerSheet{
        public:
            StickerSheet (const Image &picture, unsigned max);
            ~StickerSheet ();
            StickerSheet (const StickerSheet &other);
            const StickerSheet &operator= (const StickerSheet &other);
            void changeMaxStickers (unsigned max);
            int addSticker (Image &sticker, unsigned x, unsigned y);
            bool translate (unsigned index, unsigned x, unsigned y);
            void removeSticker (unsigned index);
            Image *getSticker (unsigned index) const;
            Image render () const;
            void copyHelper(const StickerSheet &other);
            void destroy_();



        private:
            unsigned maxpapushin;
            Image ** binky;
            unsigned *Xcoordinate;
            unsigned *Ycoordinate;
            unsigned current;
};

#endif


/*
 *Image StickerSheet::render() const {
   Image * curObj;
     Image * retImg = new Image(base);
       for(unsigned x = 0; x < arr_cnt; x++) {
           curObj = stickArr[x];

for(unsigned xC = xVal[x]; xC - xVal[x] < curObj->width(); xC++) {
    for(unsigned yC = yVal[x]; yC - yVal[x] < curObj->height(); yC++) {
    if(yC >= retImg->height()) {
        retImg->scale((retImg->height() + 1)/(retImg->height()));
        }
            if((curObj->getPixel(xC - xVal[x], yC - yVal[x]))->a != 0) {
(retImg->getPixel(xC,yC))->h = (curObj->getPixel(xC - xVal[x], yC - yVal[x]))->h;
(retImg->getPixel(xC,yC))->s = (curObj->getPixel(xC - xVal[x], yC - yVal[x]))->s;
(retImg->getPixel(xC,yC))->l = (curObj->getPixel(xC - xVal[x], yC - yVal[x]))->l;
(retImg->getPixel(xC,yC))->a = (curObj->getPixel(xC - xVal[x], yC - yVal[x]))->a;
}
}
if(xC >= retImg->width()) {
                                                                                                                           retImg->scale((retImg->width() + 1)/(retImg->width()));
                                                                                                                                 }
                                                                                                                                     }
                                                                                                                                       }
                                                                                                                                         return *retImg;
                                                                                                                                         }
*/
