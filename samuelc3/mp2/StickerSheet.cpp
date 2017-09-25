#include "StickerSheet.h"
#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max){
        maxpapushin = max;
        current = 0;
        binky = new Image[max];
        //binky[maxpapushin] = {nullptr};
        Xcoordinate = new unsigned[max];
        Ycoordinate = new unsigned[max];
        pants = new Image(picture);
}

void StickerSheet::changeMaxStickers(unsigned max){
    // make a new Sticker array called temp with size max
    //loop through binky for size min(max, sizeof(binky)) and 
    //say that the image pointer in binky is whatever index in new array
    Image * yeahboi = new Image[max];
    unsigned * Xs = new unsigned[max];
    unsigned* Ys = new unsigned[max];
    unsigned maxwei = max;
    if(maxpapushin < max){
        maxwei = current;
    }
        for(unsigned i =0; i < maxpapushin; i++){
            Xs[i] = Xcoordinate[i];
            Ys[i] = Ycoordinate[i];
            yeahboi[i] = binky[i];
    }
    delete[] binky;
    delete[] Ycoordinate;
   delete[] Xcoordinate; 
    binky = yeahboi;
    Xcoordinate = Xs;
    Ycoordinate = Ys;
    maxpapushin = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        if(current + 1>= maxpapushin)
                return -1;
        Xcoordinate[current] = x;
        Ycoordinate[current] = y;
        binky[current] = sticker;
        current++;
        return current;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    if(this == &other)
        return *this;
    destroy_();
    copyHelper(other);
    return *this;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copyHelper(other);
}

StickerSheet::~StickerSheet (){
    destroy_();
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index >= current)
            return false;
    Xcoordinate[index] = x;
    Ycoordinate[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    for(unsigned i = index; i < current - 1; i++){
        binky[i] = binky[i+1];
        Xcoordinate[i] = Xcoordinate[i+1];
        Ycoordinate[i] = Ycoordinate[i+1];
    }
    //delete binky[index];
    current = current - 1;
}

Image* StickerSheet::getSticker(unsigned index) const{
        if(index >= maxpapushin)
                return NULL;
        return &binky[index];
}

Image StickerSheet::render() const{
    Image *rip = pants;
    for(unsigned x = 0; x < current; x++){
        for(unsigned x_ = Xcoordinate[x]; x_ - Xcoordinate[x] < binky->width(); x_++){
            for(unsigned y_ = Ycoordinate[x]; y_ - Ycoordinate[x] < binky->height(); y_++){
                if(y_ > rip->height()){
                    rip->scale((rip->height() + 1)/(rip->height()));
                }
                HSLAPixel * pixel = rip->getPixel(x_, y_);
                HSLAPixel * ppiixxeell = binky[x].getPixel(x_ - Xcoordinate[x], y_ - Ycoordinate[x]);
                if(ppiixxeell->a != 0){
                    pixel -> h = ppiixxeell -> h;
                    pixel -> s = ppiixxeell -> s;
                    pixel -> l = ppiixxeell -> l;
                    pixel -> a = ppiixxeell -> a;
                    }
                }
            if( x_ < rip->width())
                    rip->scale((rip->width() + 1)/(rip->height()));
            }
        }
    return *rip;
}
void StickerSheet::destroy_(){
        delete[] binky;  
        delete[] Xcoordinate;
        delete[] Ycoordinate;
}

void StickerSheet::copyHelper(const StickerSheet &other){
    current = other.current;
    maxpapushin = other.maxpapushin;
    binky = new Image[maxpapushin];
    Ycoordinate = new unsigned[maxpapushin];
    Xcoordinate = new unsigned[maxpapushin];
    for(unsigned poo = 0; poo < current; poo++){
            binky[poo] = other.binky[poo];
            Xcoordinate[poo] = other.Xcoordinate[poo];
            Ycoordinate[poo] = other.Ycoordinate[poo];
    }
}
/*
#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
            imageList_ = new Image[max];    
                xList_ = new int[max];
                    yList_ = new int[max];
                        max_ = max;
                            imageList_[0] = picture;
                                xList_[0] = 0;
                                    yList_[0] = 0;
                                        size_ = 1;
}

StickerSheet::~StickerSheet() {
            delete[] imageList_;
                delete[] xList_;
                    delete[] yList_;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
            imageList_ = NULL;
                xList_ = NULL;
                    yList_ = NULL;
                        _copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
            if (this != &other)
                            _copy(other);
                return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
            Image* imageList = new Image[max];
                int* xList = new int[max];
                    int* yList = new int[max];
                        for (unsigned i = 0; i < max_; i++) {
                                        imageList[i] = imageList_[i];
                                                xList[i] = xList_[i];
                                                        yList[i] = yList_[i];
                                                            }
                            delete[] imageList_;
                                delete[] xList_;
                                    delete[] yList_;

                                        imageList_ = imageList;
                                            xList_ = xList;
                                                yList_ = yList;
                                                    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
            if (size_ != max_) {
                            imageList_[size_] = sticker;
                                    xList_[size_] = x;
                                            yList_[size_] = y;  
                                                    return size_++;
                                                        } else {
                                                                        return -1;
                                                                            }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
            if (index < max_ && imageList_[index].height() != 0) {
                            xList_[index] = x;
                                    yList_[index] = y;
                                            return true;
                                                } else {
                                                                return false;
                                                                    }
}

void StickerSheet::removeSticker(unsigned index) {
            if (index <= size_ - 1) {
                            for (unsigned i = index; i <= size_ - 1; i++) {
                                                imageList_[i] = imageList_[i + 1];
                                                            xList_[i] = xList_[i + 1];
                                                                        yList_[i] = yList_[i + 1];
                                                                                }
                                }
                size_--;
}

Image* StickerSheet::getSticker(unsigned index) const {
            return &imageList_[index];
}

Image StickerSheet::render() const {
            Image image = imageList_[0];
                for (unsigned i = 1; i < size_; i++) {
                                int xCoord = xList_[i];
                                        int yCoord = yList_[i];
                                                Image sticker = imageList_[i];
                                                        for (unsigned x = 0; x < sticker.width(); x++) {
                                                                            for (unsigned y = 0; y < sticker.height(); y++) {
                                                                                                    HSLAPixel* imagePixel = image.getPixel(x + xCoord, y + yCoord);
                                                                                                                    HSLAPixel* stickerPixel = sticker.getPixel(x, y);
                                                                                                                                    if (stickerPixel->a != 0){
                                                                                                                                                                imagePixel->h = stickerPixel->h;
                                                                                                                                                                                    imagePixel->s = stickerPixel->s;
                                                                                                                                                                                                        imagePixel->l = stickerPixel->l;
                                                                                                                                                                                                                            imagePixel->a = stickerPixel->a;
                                                                                                                                                                                                                                            }
                                                                                                                                                }
                                                                                    }
                                                            }
                    return image;
}

void StickerSheet::_copy(StickerSheet const &other) {
            delete[] imageList_;
                delete[] xList_;
                    delete[] yList_;

                        max_ = other.max_;
                            imageList_ = new Image[max_];
                                xList_ = new int[max_];
                                    yList_ = new int[max_];
                                        for (unsigned i = 0; i < max_; i++) {
                                                        imageList_[i] = other.imageList_[i];
                                                                xList_[i] = other.xList_[i];
                                                                        yList_[i] = other.yList_[i];
                                                                            }
}
*/
