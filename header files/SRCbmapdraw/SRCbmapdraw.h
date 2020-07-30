#include <SRCbmaps.h>

void weights(){
//oled.clearDisplay();
oled.setTextXY(3,0);
oled.drawBitmap(gainz, 1024);
}

void mando(){
oled.setTextXY(3,0);
oled.drawBitmap(boba, 1024);
}