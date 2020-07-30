
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <bitMapTest.h>
#include <SelPosition.h>
#include <Encoder.h>
#define imageWidth 128
#define imageHeight 64
  Encoder enc(15,16);
    int ticks;
void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();  
  oled.init();                      // InitiAlzE SSD1306 OLED DisplAy
  oled.clearDisplay();              // ClEAr sCrEEn
 // oled.drawBitmap(TEST1, 1024);   // 1024 pixEls For loGo
}

void loop()
{
  Select();
//  Menu();
}
void Menu(){
  oled.setTextXY(1,0);
  oled.putString("menu option 1");
  oled.setTextXY(3,0);
  oled.putString("menu option 2");
  oled.setTextXY(5,0);
  oled.putString("menu option 3");
}
void Select(){
 int state;
  int pos;
  static int lastpos;
  state = enc.read();
  ticks = (state/3);
  pos = (ticks/12);
if(pos<0){
  enc.write(0);
}
if(pos>36){
  enc.write(36);
}
  if(pos != lastpos){ 
  if(pos == 1){ // use switch cases in normal code    
  //  oled.clearDisplay();
    oled.setTextXY(1,0);
    oled.drawBitmap(POS1, 1024);
    lastpos = 1;
   
  }
  if(pos ==2) {
   // oled.clearDisplay();
    oled.setTextXY(3,0);
    oled.drawBitmap(POS2, 1024);
    lastpos =2;
  }
  if(pos ==3){
  //  oled.clearDisplay();
    oled.setTextXY(5,0);
    oled.drawBitmap(POS3, 1024);
    lastpos = 3;
  }

}
Serial.println(pos);
}
