#include "StickerSheet.h"
#include <iostream>
#include "Image.h"
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max){
        maxpapushin = max;
        binky = new unsigned[max -1];
        coordinate = new unsigned[max - 1][max -1];
        lay = new unsigned[max-1];
        addSticker(picture, 0, 0);
}

void StickerSheet::changeMaxStickers(unsigned max){
    // make a new Sticker array called temp with size max
    //loop through binky for size min(max, sizeof(binky)) and 
    //say that the image pointer in binky is whatever index in new array
    StickerSheet * yeahboi = new StickerSheet(binky[0], max);
    
    for(unsigned i = 0; i < max - 1; i++){
        for(unsigned j = 0; j < max - 1; j++){
            yeahboi->coordinate[i][j] = this->coordinate[i][j];
    }
            yeahboi->lay[i] = this->lay[i];
            yeahboi->binky[i] = this->binky[i];
    }
    this = yeahboi;
    
}



StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    if(this == &other)
        return *this;
    destroy_();
    copyHelper(other);
}


StickerSheet::~StickerSheet (){
    destroy_();
}


//void StickerSheet::destroy_(){
  //          for(unsigned i = 0; i < maxpapushin - 1; i++) delete[];
      //      delete[][] this-> coordinate;
    //        delete[] this-> lay;
//}

void StickerSheet::copyHelper(const StickerSheet &other){
    maxpapushin = other.maxpapushin;
    binky = new unsigned[mapapushin - 1];
    coordinate = new unsigned[maxpapushin - 1][maxpapushin-1];
    lay = new unsigned[maxpapushin-1];    

    for(unsigned i = 0; i < maxpapushin - 1; i++){
        for(unsigned j = 0; j < maxpapushin - 1; j++){
            coordinate[i][j] = other.coordinate[i][j];
    }
            lay[i] = other.lay[i];
            binky[i] = other.binky[i];
}
