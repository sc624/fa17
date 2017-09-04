#include <string>
#include "cs225/PNG.h"
#include "mp1.h"
using namespace cs225;
void rotate(std::string inputFile, std::string outputFile) {
	PNG input;
	PNG output;
	input.readFromFile(inputFile);
	int imagewidth = input.width();
	int imageheight = input.height();
	for(unsigned x = 0; x < imagewidth; x++){
		for(unsigned y = 0; x < imageheight; y++){
		HSLAPixel *inputPixel = input.getPixel(x,y);
		HSLAPixel *outputPixel = output.getPixel(imagewidth - x, imageheight - y);
		}
	}
	 output.writeToFile(outputFile);
}
