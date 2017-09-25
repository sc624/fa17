#include "StickerSheet.h"

using namespace std;

int main() {
      
  Image windows;
  windows.readFromFile("lojmr.png");
 
     Image rug;
    rug.readFromFile("images.png");
    Image vacuum;
    vacuum.readFromFile("index.jpg");
    Image chair;
    chair.readFromFile("14409535.jpg");

  StickerSheet sheet(windows, 5);

    sheet.addSticker(rug, 900, 200);
    sheet.addSticker(vacuum, 1000, 250);
    sheet.addSticker(chair, 1300, 150);

    sheet.render();
    Image done;
    done.writeToFile("myImage.png");
    
    return 0;
}
