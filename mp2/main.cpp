#include "StickerSheet.h"

using namespace std;

int main() {
      
  Image windows;
  windows.readFromFile("lojmr.png");
 
    Image rug;
    rug.readFromFile("images.png");
    Image vacuum;
    vacuum.readFromFile("index.png");
    Image chair;
    chair.readFromFile("14409535.png");

  StickerSheet sheet(windows, 5);

    sheet.addSticker(rug, 0, 0);
    sheet.addSticker(vacuum, 0, 0);
    sheet.addSticker(chair,100,100);
    sheet.changeMaxStickers(10);
    sheet.translate(2, 100, 250);
    sheet.removeSticker(1);
    sheet.addSticker(vacuum, 200, 200);
    Image done = sheet.render();
    done.writeToFile("myImage.png");
    
    return 0;
}
