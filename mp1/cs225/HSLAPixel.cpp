#include "HSLAPixel.h"
namespace cs225{
	HSLAPixel::HSLAPixel():HSLAPixel(0,0,1,1){
	}
	HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
		h=hue;
		s=saturation;
		l=luminance;
		a=1;
	}
	HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
		h=hue;
		s=saturation;
		l=luminance;
		a=alpha;
	}
}


