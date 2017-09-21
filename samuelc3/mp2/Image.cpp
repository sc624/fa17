#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/RGB_HSL.h"
#include "cs225/lodepng/lodepng.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

using namespace std;
using namespace cs225;
void Image::lighten(){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> l = pic -> l + 0.1;
                    if(pic -> l>1)
                            pic->l = 1;
                    }
                }
            }
void Image::lighten(double amount){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> l = pic -> l + amount;
                    if(pic -> l>1)
                        pic->l = 1;
                    }
                }    
    }
void Image::darken(){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> l = pic -> l - 0.1;
                    if(pic -> l < 0)
                            pic -> l = 0;
                    }
                }    
            }
void Image::darken(double amount){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> l = pic -> l - amount;
                    if(pic -> l < 0)
                            pic -> l = 0;
                    }
                }    
            }
void Image::saturate(){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> s = pic -> s + 0.1;
                    }
                }    
            }
void Image::saturate(double amount){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> s = pic -> s + amount;
                    }
                }    
            }
void Image::desaturate(){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> s = pic -> s - 0.1;
                    }
                }    
            }
void Image::desaturate(double amount){
        for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> s = pic -> s - amount;
                    }
                }    
            }
void Image::grayscale(){
    for(unsigned x = 0; x < this->width(); x++){
		    for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel * pic = this->getPixel(x,y);
                pic -> s = 0;
                    }
                }
            }
void Image::rotateColor(double degrees){
    for(unsigned x = 0; x < this->width(); x++){
	    for(unsigned y = 0; y < this->height(); y++){
              HSLAPixel * pic = this->getPixel(x,y);
              pic -> h = pic -> h + degrees;
              if(pic -> h > 360){
                pic -> h = pic -> h - 360;
                         }
              if(pic -> h < 0){
                pic->h = pic->h+360;
              }      
                    }
                }
    }
void Image::illinify(){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
	        HSLAPixel *pixel = this->getPixel(x, y);
	            if(pixel -> h > 113.5 && pixel -> h < 293.5){
		pixel -> h = 216;
		}
	if(((pixel -> h <= 113.5) && (pixel->h >= 0)) || ((pixel -> h >= 293.5) && (pixel->h <= 360))){
		pixel -> h = 11;
		    } 
	    }
    }
}
void Image::scale(double factor){
        unsigned scaleX = this->width() * factor;
        unsigned scaleY = this->height() * factor;
        PNG * picture = new PNG(scaleX, scaleY);

        double xx, yy;
        for (unsigned int y = 0; y < scaleY; y++){
            for(unsigned int x = 0; x < scaleX; x++){
                xx = floor(x / factor);
                yy = floor(y / factor);
                HSLAPixel * pixel = this->getPixel(xx,yy);
                HSLAPixel * ppiixxeell = picture->getPixel(x,y);

                ppiixxeell -> h = pixel -> h;
                ppiixxeell -> s = pixel -> s;
                ppiixxeell -> l = pixel -> l;
                ppiixxeell -> a = pixel -> a;
            }
        }
        this->resize(scaleX, scaleY);
        for (unsigned int x = 0; x < scaleX; x++){
            for(unsigned int y = 0; y <scaleY; y++){
                HSLAPixel * pic = this->getPixel(x,y);
                HSLAPixel * pic2 = picture->getPixel(x,y);
                pic -> h = pic2 -> h;
                pic -> s = pic2 -> s;
                pic -> l = pic2 -> l;
                pic -> a = pic2 -> a;
            }
            }
}

void Image::scale(unsigned w, unsigned h){
    double wfactor = (double)w / (double)this->width();
    double hfactor = (double)h / (double)this->height();
    

    if(hfactor > wfactor)
            this->scale(wfactor);
    else if(wfactor >= hfactor)
            this->scale(hfactor);
}
