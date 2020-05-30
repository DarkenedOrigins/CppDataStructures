#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
	PNG image;
	image.readFromFile(inputFile);
	int width = image.width();
	int height = image.height();
	PNG imageOut(width,height);
	for(int y=0;y<height;y++){
		for(int x=0; x<width;x++){
      			HSLAPixel *pixel = image.getPixel(x, y);
			HSLAPixel *RotatedPixel = imageOut.getPixel(width-1-x,height-1-y);
			RotatedPixel->h = pixel->h;
			RotatedPixel->s = pixel->s;
			RotatedPixel->l = pixel->l;
			RotatedPixel->a = pixel->a;
		}
	}
	imageOut.writeToFile(outputFile);
	return;
}
