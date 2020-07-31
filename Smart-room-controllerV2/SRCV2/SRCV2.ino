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
     bool star = false;
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
 // long press for off?
 
}

void loop() { // main code. menu and submenu displays and options to select.
 luminosity();
  temp = (bme.readTemperature() * 9/5)+32;
  pres = (bme.readPressure() /100.0f)/68.9476;
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA)*3.28084;
  hum = bme.readHumidity();
// make void for displaying ethernet status on oled
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
            case 1:
            Serial.println("SM 1");           
              
             //sol(); //bmap dont forget the if statement for snowflake
             
             if (star == false){
              sol();
              star = true;
             }
             
             bmeValT(temp);
              break;             
            case 2:
              bmeValP(pres);
            //  weights(); bmap
            Serial.println("SM 2");
              break;
            case 3:
              bmeValA(alt);
              Serial.println("SM 3");
              break;
            case 4:
            bmeValH(hum);
            moisture(); //bmap
            Serial.println("SM 4");
              break;          
          }   
      break;
    case 2:
      Serial.println("two");
      smartMenu = true;
        switch(s){
          case 0:
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
      userManual();
      delay(10000);
      oled.clearDisplay();
      i=0;
      Serial.println("three");
      break;
    case 4:
       //PWR(); bmap
        
      Serial.println("four");
      break;  
  }
  Serial.print(n);
 smartStateLed();
 // wemoSet();
 //hueSet();
 NeoRing();

}
void click1(){ // calling click function from one button library. used to select menus and menu options.
  buttonState =! buttonState;
  oled.clearDisplay();
  if(subMenu == true && smartMenu == false){ 
    n = (enc.read()/24);
  }
    else if (subMenu == false){
            if(smartMenu == true){
            s = (enc.read()/48);
            }
    
   else {
      i = (enc.read()/24);
    }
    }

}
void doubleclick1(){ // calling the double click function from One Button library.
  DBclick =! DBclick;
  oled.clearDisplay();
  enc.write(0);
  s=0;
  n=0;
  i=0;
}
void smartStateLed(){ // function for displaying wether or not smart control is on
 if(smartControl == true){
  digitalWrite(ledPin, HIGH);
}
 if(smartControl == false){
  digitalWrite(ledPin,LOW);
 }
}

void bmeValT(float ptemp){ // function to display temperature
  oled.setTextXY(0,0);
  oled.putString(float(ptemp));
}
void bmeValP(float ppres){ // function to display pressure
  oled.setTextXY(0,0);
  oled.putString(float(ppres));
}
void bmeValA(float palt){  // function to display altitude
  oled.setTextXY(0,0);
  oled.putString(float(palt));
}
void bmeValH(float phum){ //function to display humidity
  oled.setTextXY(0,0);
  oled.putString(float(phum));
}
void openingmessage(){
  oled.setTextXY(0,0);
  // if statement for ethernet status
}
void wemoSet(){ // function for smart control to use the wemo pins. 
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

void hueSet(){ // dont forget to make an activation for hue.
  if( hueState == true){ // just turn on for when Neopix turn on or smart control on.
  onoff =! onoff;
  }
  if(onoff==true){
  activated=true;
  bulb = 2;
  if(smartControl == true){
  setHue(bulb, activated,colorShift[showTemp],luminosity()); //photoresistor value
  }
  if(smartControl == false){
  setHue(bulb, activated,colorShift[showTemp],250); //photoresistor value
  } 
}
}

void NeoRing(){ // function for using NeoPixel ring. Also uses smart control.
    showTemp = temp;
    showTemp = map(showTemp, 0, 100, 0, 12);
    if (smartControl == false){ // smart control is name of intelligent control func.
    pixel.clear();
    pixel.setPixelColor(showTemp,colorShift[showTemp]);
    pixel.setBrightness(250);//use photo resistor value
    pixel.show();
    }
    if (smartControl == true){
    pixel.clear();
    pixel.setPixelColor(showTemp,colorShift[showTemp]);
    pixel.setBrightness(luminosity());//use photo resistor value
    pixel.show();
    Serial.println(luminosity());
    }
}

unsigned int luminosity(){ // function for using a photoresistor to change NeoPixel and hue brightness
  int pResistor = 14; 
  int pSenseVal;
  int analogVal;
  int bitSenseVal;
  pSenseVal = analogRead(pResistor);
  bitSenseVal = map(pSenseVal, 0, 1023, 0, 255);  // raise bottom number for dim
  return bitSenseVal;
}
