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
void moisture(){
oled.setTextXY(0,0);
oled.drawBitmap(humidity,1024);
}
void sol(){
oled.setTextXY(0,0); // its refreshing too fast
oled.drawBitmap(sun,1024); 
}
void PWR(){
oled.setTextXY(5,0);
oled.drawBitmap(powerSymbol,1024);
}