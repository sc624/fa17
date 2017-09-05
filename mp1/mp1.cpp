#include <string>
#include "cs225/PNG.h"
#include "mp1.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;
void rotate(std::string inputFile, std::string outputFile) {
	PNG input, output;
	input.readFromFile(inputFile);
	output = PNG(input.width(), input.height());
	for(unsigned x = 0; x < input.width(); x++){
		for(unsigned y = 0; y < input.height(); y++){
		HSLAPixel *inputPixel = input.getPixel(x,y);
		HSLAPixel *outputPixel = output.getPixel(input.width() - 1 - x, input.height() - 1 - y);
		outputPixel->h = inputPixel->h;
		outputPixel->s = inputPixel->s;
		outputPixel->l = inputPixel->l;
		outputPixel->a = inputPixel->a;
		}
	}
	 output.writeToFile(outputFile);
}
