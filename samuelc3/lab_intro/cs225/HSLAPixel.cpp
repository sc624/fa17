#include "HSLAPixel.h"
using namespace cs225;
cs225::HSLAPixel::HSLAPixel(){
	a = 1.0;	
}
cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
	h = hue;
	s = saturation;
	l = luminance;
	a = 1.0;
}
cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){	
	h = hue;
	s = saturation;
	l = luminance;
	a = alpha;

}
