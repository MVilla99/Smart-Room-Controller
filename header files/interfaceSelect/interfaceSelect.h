/* written by mauricio villa courtesy of his big ol' brain ;) */

#include <SelPosition.h>
// needs an encoder with encoder.h initialized in main code to be able to run.
// Serial print of int pos at the bottom of code, remove if you dont want to see pos on serial monitor.
	//four arrow position
void Select1(){
 int state;
  int pos;
  static int lastpos;
  state = enc.read();
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
		
	//four arrow position for use elesewhere
void Select2(){
 int state2;
  int pos2;
  static int lastpos2;
  state2 = enc.read();
  pos2 = (state2/24); // directly read from enc and 96/24 was 4 pos needed
if(pos2<0){
  enc.write(0);
}
if(pos2>5){
  enc.write(96);
}
  if(pos2 != lastpos2){ 
  if(pos2 == 1){ // use switch cases in normal code    
    oled.setTextXY(1,0);
    oled.drawBitmap(POS14, 1024);
    lastpos2 = 1;
  }
  if(pos2 ==2) {
    oled.setTextXY(2,0);
    oled.drawBitmap(POS24, 1024);
    lastpos2 =2;
  }
  if(pos2 ==3){
    oled.setTextXY(4,0);
    oled.drawBitmap(POS34, 1024);
    lastpos2 = 3;
  }
  if(pos2 ==4){
  oled.setTextXY(6,0);
  oled.drawBitmap(POS44, 1024);
  lastpos2 = 4;
  }

}
Serial.println(pos2);
}

	//four arrow position for use elsewhere elsewhere
void Select3(){
 int state3;
  int pos3;
  static int lastpos3;
  state3 = enc.read();
  pos3 = (state3/24); // directly read from enc and 96/24 was 4 pos needed
if(pos3<0){
  enc.write(0);
}
if(pos3>5){
  enc.write(96);
}
  if(pos3 != lastpos3){ 
  if(pos3 == 1){ // use switch cases in normal code    
    oled.setTextXY(1,0);
    oled.drawBitmap(POS14, 1024);
    lastpos3 = 1;
  }
  if(pos3 ==2) {
    oled.setTextXY(2,0);
    oled.drawBitmap(POS24, 1024);
    lastpos3 =2;
  }
  if(pos3 ==3){
    oled.setTextXY(4,0);
    oled.drawBitmap(POS34, 1024);
    lastpos3 = 3;
  }
  if(pos3 ==4){
  oled.setTextXY(6,0);
  oled.drawBitmap(POS44, 1024);
  lastpos3 = 4;
  }

}
Serial.println(pos3);
}

	//four arrow position for use elsewhere elsewhere ELSEWHERE!!!
void Select4(){
 int state;
  int pos;
  static int lastpos;
  state = enc.read();
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

	//you know what it is...
void SelectSM(){
 int state;
  int pos;
  static int lastpos;
  state = enc.read();
  pos = (state/48); // directly read from enc and 96/24 was 4 pos needed
if(pos<0){
  enc.write(0);
}
if(pos>2){
  enc.write(96);
}
  if(pos != lastpos){ 
  if(pos == 1){ // use switch cases in normal code    
    oled.setTextXY(4,0);
    oled.drawBitmap(POS34, 1024);
    lastpos = 1; 
  }
  if(pos ==2) {
    oled.setTextXY(6,0);
    oled.drawBitmap(POS44, 1024);
    lastpos =2;
  }
  
}
Serial.println(pos);
}
