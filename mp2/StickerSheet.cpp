#include "StickerSheet.h"
#include <iostream>
#include "Image.h"
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max){
        maxpapushin = max;
        current = 0;
        //binky = new Image*[max];
        binky[maxpapushin] = {nullptr};
        Xcoordinate = new unsigned[max];
        Ycoordinate = new unsigned[max];
        Image photo = picture;
        addSticker(photo, 0, 0);
}

void StickerSheet::changeMaxStickers(unsigned max){
    // make a new Sticker array called temp with size max
    //loop through binky for size min(max, sizeof(binky)) and 
    //say that the image pointer in binky is whatever index in new array
    StickerSheet * yeahboi = new StickerSheet(*binky[0], max);
    unsigned maximum = min(maxpapushin, max);
    for(unsigned i = 0; i < maximum - 1; i++){
            yeahboi->Ycoordinate[i] = this->Ycoordinate[i];
            yeahboi->Xcoordinate[i] = this->Xcoordinate[i];
            *(yeahboi->binky[i]) = *(this->binky[i]);
    }
    *this = *yeahboi;
    
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        if(current >= maxpapushin)
                return -1;
        Xcoordinate[current] = x;
        Ycoordinate[current] = y;
        current++;
        binky[current] = &sticker;
        return current;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    if(this == &other)
        return *this;
    destroy_();
    copyHelper(other);
    return *this;
}

StickerSheet::~StickerSheet (){
    destroy_();
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(binky == nullptr || index >= maxpapushin)
            return false;
    Xcoordinate[index] = x;
    Ycoordinate[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    for(unsigned i = index; i < maxpapushin - 1; i++){
        *binky[i] = *(binky[i+1]);
    }
    delete binky[index];
    current = current - 1;
}

Image* StickerSheet::getSticker(unsigned index) const{
        if(index >= maxpapushin)
                return NULL;
        return binky[index];
}

Image StickerSheet::render() const{
    unsigned width_ = 0, height_ = 0, temp;
    for(unsigned i = 0; i < maxpapushin; i++){
        temp = Xcoordinate[i] + binky[i]->width();
        if(temp > width_)
            width_ = temp;
        temp = Ycoordinate[i] + binky[i]->height();    
        if(temp > height_)
            height_ = temp;
        }

    PNG *orbitgum = new PNG(width_, height_);
    for(unsigned layer = 0; layer < maxpapushin; layer++){
        for(unsigned x = Xcoordinate[layer]; x < binky[layer]->width(); x++){
            for(unsigned y = Ycoordinate[layer]; y < binky[layer]->height(); y++){
                HSLAPixel *pixel = orbitgum->getPixel(x,y);
                HSLAPixel *ppiixxeell = binky[layer]->getPixel(Xcoordinate[layer],Ycoordinate[layer]);
                pixel -> h = ppiixxeell -> h;
                pixel -> s = ppiixxeell -> s;
                pixel -> l = ppiixxeell -> l;
                if(ppiixxeell -> a != 0) 
                        pixel -> a = ppiixxeell -> a;
            }
        }
    }
    return orbitgum;
}

void StickerSheet::destroy_(){
    for(unsigned i = 0; i < maxpapushin; i++)
        delete binky;  
        delete[] Xcoordinate;
        delete[] Ycoordinate;
}

void StickerSheet::copyHelper(const StickerSheet &other){
    current = other.current;
    maxpapushin = other.maxpapushin;
    //binky = new Image*[maxpapushin];
    binky[maxpapushin] = {nullptr};
    Ycoordinate = new unsigned[maxpapushin];
    Xcoordinate = new unsigned[maxpapushin];
    for(unsigned poo = 0; poo < maxpapushin; poo++){
            *(binky[poo]) = *(other.binky[poo]);
            Xcoordinate[poo] = this->Xcoordinate[poo];
            Ycoordinate[poo] = this->Ycoordinate[poo];
    }
}
