// testing for one button switch case
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <colorshift.h>
#include <OneButton.h>
#include <Encoder.h>
  Encoder enc(15,16);
#include <interfaceMenu.h>
#include <interfaceSelect.h>
#include <SPI.h>
#include <Ethernet.h>
  IPAddress ip(192,168,1,4);
#include <mac.h>
#include <wemo.h>
#include <hue.h>
#include <pin13.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <SRCbmapdraw.h>
  #define imageWidth 128
  #define imageHeight 64
  #define SEALEVELPRESSURE_HPA (1013.25)
    Adafruit_BME280 bme;   
    float temp;
    float pres;
    float hum;
    float alt;
int encButton = 17;
int menuButton = 20;
OneButton button1(encButton,false); // try with normal button 
bool buttonState = HIGH;
bool DBclick = LOW;
bool subMenu = false;
int i;
int s;
static int n;
int pwr;
  int bulb;
  bool activated;
  bool onoff = false;
  bool last = HIGH;
int ledPin = 8;
Adafruit_NeoPixel pixel(12, 20, NEO_GRB + NEO_KHZ800);
int showTemp;
int colorShift[] = {blue4,blue3,blue2,blue1,blue0,mid1,mid2,red0,red1,red2,red3,red4}; 
  bool smartControl = false;
  bool smartMenu = false;
  bool pwrMenu = false;
  bool hueState = false;
void setup() {
  // put your setup code here, to run once:
pinMode(menuButton, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(10, OUTPUT);
pixel.begin();
pixel.show();
Serial.begin(9600);
Ethernet.begin(mac,ip);
while(!Serial);
Wire.begin();
oled.init();
oled.clearDisplay();
  unsigned bmestat;
  bmestat = bme.begin(0x76); 
button1.attachClick(click1);
button1.attachDoubleClick(doubleclick1);
button1.setClickTicks(250);
button1.setPressTicks(2000);
 
}

void loop() {
  temp = (bme.readTemperature() * 9/5)+32;
  pres = (bme.readPressure() /100.0f)/68.9476;
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA)*3.28084;
  hum = bme.readHumidity();

button1.tick();
  subMenu = false;
  smartMenu = false;
  switch(i){
    
    case 0:
    Menu();
    Select1();
      break;
    case 1:  // use enc "ticks" mapped to each S-C statement and the button will act as the select
     subMenu = true;     
            switch(n){              
            case 0:
            Serial.println("SM 0");
            bmeMenu();
            Select2();
              break;
            case 1: // SMarray[x,y,z,q] n = SMarray[]
            Serial.println("SM 1");           
              bmeValT(temp);
              break;             
            case 2:
              bmeValP(pres);
            Serial.println("SM 2");
              break;
            case 3:
              bmeValA(alt);
              Serial.println("SM 3");
              break;
            case 4:
            bmeValH(hum);
            Serial.println("SM 4");
              break;          
          }   
      break;
    case 2:
      Serial.println("two");
      smartMenu = true;
        switch(s){
          case 0:
          //menu options
          SmartStatMenu();
          SelectSM();
         break;
          case 1:
          SSMyes();
         smartControl = true;
         hueState = true;
         delay(5000);
         s=0;
         i=0;
         oled.clearDisplay();
         break;
          case 2:
          //no function, s=0 and smartControl = false
           SSMno();
          smartControl = false;
          delay(5000);
          s=0;
          i=0;
          oled.clearDisplay();
          
         break;
        }  
      break;
    case 3:
      userManual(); // doesnt return to main. maybe because no scroll funct.?
      // put smart control func. in here. 
      delay(10000);
      oled.clearDisplay();
      i=0;
      Serial.println("three");
      break;
    case 4:
      pwrMenu = true;
        switch(pwr){
          
          case 0:
          SelectPWR();
          powerSel();
            break;
          case 1:
          oled.setTextXY(0,0);
          oled.putString("powering off");
          oled.setTextXY(2,0);
          oled.putString("thank you for");
          oled.setTextXY(4,0);
          oled.putString("use of this SRC");
            break;
          case 2:
            break;
        }
      Serial.println("four");
      break;  
  }
  Serial.print(n);
 smartStateLed();
 // wemoSet();
 //hueSet();
 NeoRing();

}
void click1(){
  buttonState =! buttonState;
  oled.clearDisplay();
  if(subMenu == true && smartMenu == false){ 
    n = (enc.read()/24);
  }
    else if (subMenu == false){
            if(smartMenu == true){
            s = (enc.read()/48);
            }
    }
    else if (pwrMenu == true){
      pwr = (enc.read()/48);
    }
   else {
      i = (enc.read()/24);
    }
    

}
void doubleclick1(){
  DBclick =! DBclick;
  oled.clearDisplay();
  enc.write(0);
  s=0;
  n=0;
  i=0;
}
void smartStateLed(){
 if(smartControl == true){
  digitalWrite(ledPin, HIGH);
}
 if(smartControl == false){
  digitalWrite(ledPin,LOW);
 }
}

void bmeValT(float ptemp){
  oled.setTextXY(0,0);
  oled.putString(float(ptemp));
}
void bmeValP(float ppres){
  oled.setTextXY(0,0);
  oled.putString(float(ppres));
}
void bmeValA(float palt){
  oled.setTextXY(0,0);
  oled.putString(float(palt));
}
void bmeValH(float phum){
  oled.setTextXY(0,0);
  oled.putString(float(phum));
}

void wemoSet(){
  /*
   * for intelligent control, boolean for int control will (smartControl)
   * set wemoSet on and off and use void for brightness for hue
   */
  //int wemoHot = 3;
//  int wemoCold = 2;
  int wemo;
  int lasttemp;  //put timer code for reading every 5 min
   // if(temp >= 70 && temp <=75){ // find way to make range from 70 - 75
  //  switchOFF(wemo);
    //switchOFF(wemoHot);
    //}
   if(temp<=69){
    wemo = 1;
   switchON(wemo);
   if(/*temp =! lasttemp && */temp<=69){
   switchOFF(2);
    }
   }
   if(temp>=70){
    wemo = 2;
   switchON(wemo);
   if(/*temp =! lasttemp && */temp>=75){
   switchOFF(wemo);
    }
   }  
   
}
/*
void hueSet(){
  if( hueState == true){ // just turn on for when Neopix turn on 
  onoff =! onoff;
  }
  if(onoff==true){
  activated=true;
  bulb = 2;
  if(smartControl == true){
  setHue(bulb, activated,colorshift[showTemp],luminosity()); //photoresistor value
  }
  if(smartControl == false){
  setHue(bulb, activated,colorshift[showTemp],250); //photoresistor value
  }
  //^^ get color from neopixel color array
 // ^^ and brightness from photoresistor 
  
}
*/
void NeoRing(){
  //int showTemp;
    showTemp = temp;
    showTemp = map(showTemp, 0, 100, 0, 12);
    if (smartControl == false){ // smart control is name of intelligent control func.
    pixel.setPixelColor(showTemp,colorShift[showTemp]);
    pixel.setBrightness(250);//use photo resistor value
    pixel.show();
    }
    if (smartControl == true){
    pixel.setPixelColor(showTemp,colorShift[showTemp]);
    pixel.setBrightness(luminosity());//use photo resistor value
    pixel.show();
    }
}

unsigned int luminosity(){
  int pResistor = 14; //or whatever number signal is
  int pSenseVal;
  int bitSenseVal;
  pSenseVal = digitalRead(pResistor);
  bitSenseVal = map(pSenseVal, 0, 10230, 0, 255);  // average looks like 5k so maybe map that
  return bitSenseVal;
}
