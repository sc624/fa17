#include "StickerSheet.h"
#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max){
        maxpapushin = max;
        current = 0;
        binky = new Image[maxpapushin];
        //binky[maxpapushin] = {nullptr};
        Xcoordinate = new unsigned[maxpapushin];
        Ycoordinate = new unsigned[maxpapushin];
        pants = picture;
}

void StickerSheet::changeMaxStickers(unsigned max){
    // make a new Sticker array called temp with size max
    //loop through binky for size min(max, sizeof(binky)) and
    //say that the image pointer in binky is whatever index in new array
    Image * yeahboi = new Image[max];
    unsigned * Xs = new unsigned[max];
    unsigned* Ys = new unsigned[max];
    unsigned maxwei;
    if(maxpapushin < max){
        maxwei = current;
    }
    else
      maxwei = max;
    

    current = maxwei;
        for(unsigned i =0; i < maxwei; i++){
            Xs[i] = Xcoordinate[i];
            Ys[i] = Ycoordinate[i];
            yeahboi[i] = binky[i];
    }
    delete[] binky;
    binky = NULL;
    delete[] Ycoordinate;
    Ycoordinate = NULL;
    delete[] Xcoordinate;
    Xcoordinate = NULL;
    binky = yeahboi;
    Xcoordinate = Xs;
    Ycoordinate = Ys;
    maxpapushin = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        if(current>= maxpapushin)
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
    if(index > current){
        return;
    }
    for(unsigned i = index; i < current - 1; i++){
        binky[i] = binky[i+1];
        Xcoordinate[i] = Xcoordinate[i+1];
        Ycoordinate[i] = Ycoordinate[i+1];
    }

    //delete binky[index];
    current = current - 1;
}

Image* StickerSheet::getSticker(unsigned index) const{
        if(index >= current)
                return NULL;
        return &binky[index];
}

Image StickerSheet::render() const{
    Image *rip =new Image(pants);
    for(unsigned x = 0; x < current; x++){
        for(unsigned x_ = Xcoordinate[x]; x_ - Xcoordinate[x] < binky[x].width(); x_++){
            for(unsigned y_ = Ycoordinate[x]; y_ - Ycoordinate[x] < binky[x].height(); y_++){
                if(y_ >= rip->height()-1){
                    rip->resize(rip->width(), rip->height()+1);
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
            if( x_ >= rip->width()-1)
                    rip->resize(rip->width() + 1,rip->height());
            }
        }
    return *rip;
}
void StickerSheet::destroy_(){
        delete[] binky;
        binky = NULL;
        delete[] Xcoordinate;
        Xcoordinate = NULL;
        delete[] Ycoordinate;
        Ycoordinate = NULL;
}

void StickerSheet::copyHelper(const StickerSheet &other){
    current = other.current;
    maxpapushin = other.maxpapushin;
    pants = other.pants;
    binky = new Image[other.maxpapushin];
    Ycoordinate = new unsigned[other.maxpapushin];
    Xcoordinate = new unsigned[other.maxpapushin];
    for(unsigned poo = 0; poo < other.maxpapushin; poo++){
            binky[poo] = other.binky[poo];
            Xcoordinate[poo] = other.Xcoordinate[poo];
            Ycoordinate[poo] = other.Ycoordinate[poo];
    }
}
