#include <bitMapTest.h>
#include <SelPosition.h>
#include <Encoder.h>
  Encoder enc(15,16);
    int ticks;

void Menu(){
  oled.setTextXY(0,0);
  oled.putString("menu option 1");
  oled.setTextXY(2,0);
  oled.putString("menu option 2");
  oled.setTextXY(4,0);
  oled.putString("menu option 3");
  oled.setTextXY(6,0);
  oled.putString("menu option 4");
}
void Select(){
 int state;
  int pos;
  static int lastpos;
  state = enc.read();
  //ticks = (state/4);
  pos = (state/24); // directly read from enc and 96/24 was 4 pos needed
if(pos<0){
  enc.write(0);
}
if(pos>5){
  enc.write(96);
}
  if(pos != lastpos){ 
  if(pos == 1){ // use switch cases in normal code    
    oled.setTextXY(1,0);
    oled.drawBitmap(POS14, 1024);
    lastpos = 1;
	
   
  }
  if(pos ==2) {
    oled.setTextXY(2,0);
    oled.drawBitmap(POS24, 1024);
    lastpos =2;
  }
  if(pos ==3){
    oled.setTextXY(4,0);
    oled.drawBitmap(POS34, 1024);
    lastpos = 3;
  }
  if(pos ==4){
  oled.setTextXY(6,0);
  oled.drawBitmap(POS44, 1024);
  lastpos = 4;
  }

}
Serial.println(pos);
}
void Menu2(){
oled.clearDisplay();
oled.setTextXY(3,3);
oled.putString("menu 2 test");
}
void Menu3(){
oled.clearDisplay();
oled.setTextXY(0,0);
oled.putString("menu3 opt.1");
oled.setTextXY(2,0);
oled.putString("menu3 opt.2");
oled.setTextXY(4,0);
oled.putString("menu3 opt.3");
oled.setTextXY(6,0);
oled.putString("menu3 opt.4");
}