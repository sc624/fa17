#include "StickerSheet.h"

using namespace std;

int main() {
      
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.render();
        return 0;
}
