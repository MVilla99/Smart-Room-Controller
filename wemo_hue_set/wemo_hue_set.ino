#include <Ethernet.h>
#include <SPI.h>
#include <mac.h>
#include <wemo.h>
#include <hue.h>
#include <ACROBOTIC_SSD1306.h>
  IPAddress ip(192,168,1,4); // run ethernet scan to be sure
  int bulb;
  bool activated;
  bool onoff = false;
  bool last = HIGH;
void setup() {
  // put your setup code here, to run once:
pinMode(10,OUTPUT);
Serial.begin(9600);
Ethernet.begin(mac,ip);
delay(2000);
Wire.begin();
oled.init();
oled.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void hueSet(){
  /*
  if(wearabledetect == true){
  onoff =! onoff;
  }
  if(onoff==true){
  activated=true;
  bulb = 2;
  setHue(bulb, activated,"color","brightness");
  ^^ get color from neopixel color array
  ^^ and brightness from photoresistor
  oled.setTextXY(0,0);
  oled.putString("lights set to:");
  oled.setTextXY(0,2);
  oled.putString("color");
 */
}
void wemoSet(){
  int wemoHot = 3;
  int wemoCold = 2;
  int lasttemp; //timer code for reading ever 5 min
  /*
    if(temp >= 70 && temp <=75){ // find way to make range from 70 - 75
    switchOFF(wemoCold);
    switchOFF(wemoHot);
    }
   if("temp read in cold range"){
   switchON(wemoCold);
   if(temp =! lasttemp && temp<=69){
   switchOFF(wemoCold);
    }
   }

   if("temp read in the hot range"){
   switchOn(wemoHot);
   if(temp =! lasttemp && temp>=75){
   switchOFF(wemoHot);
    }
   }  
   */
}
