#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;
int main() {
	Image alma;
	alma.readFromFile("alma.png");
	StickerSheet yay(alma,3);
	Image shifu;
	shifu.readFromFile("Squirrel-icon.png");
	yay.addSticker(shifu,20,344);
	Image batman;
	batman.readFromFile("batman-23-xxl.png");
	yay.addSticker(batman,322,10);
	Image jack;
	jack.readFromFile("Jack-Frost-icon.png");
	yay.addSticker(jack,645,344);
	Image output=yay.render();
	output.writeToFile("myImage.png");
  return 0;
}
