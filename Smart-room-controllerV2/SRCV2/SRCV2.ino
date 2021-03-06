/*written by mauricio villa.
 *completed on 1-August-2020
 *Smart room controller for use with wemo,hue,and neopixels 
 *Deep Dive Coding, IoT, Cohort 2
 */
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
OneButton button1(encButton,false);

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
  bool startState = false;
//booleans for bitmap states during bme read menu.      
     bool star = false;
     bool frost = false;
     bool drip = false;
     bool thicc = false;
     bool zap = false;
     bool bars = false;
     bool nobars = false;
int ledPin = 8;
Adafruit_NeoPixel pixel(12, 20, NEO_GRB + NEO_KHZ800);
int showTemp;
int colorShift[] = {blue4,blue3,blue2,blue1,blue0,mid1,mid2,red0,red1,red2,red3,red4}; 
  bool smartControl = false;
  bool smartMenu = false;
  bool pwrMenu = false;
  bool hueState = false;
  bool wemoState = false;
void setup() {
  // put your setup code here, to run once:
pinMode(menuButton, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(10, OUTPUT);
pixel.begin();
pixel.show();
Serial.begin(9600);
Ethernet.begin(mac,ip);
delay(2000);
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
// dont forget servo code.
void loop() { // main code. menu and submenu displays and options to select.
 luminosity();
  temp = (bme.readTemperature() * 9/5)+32;
  pres = (bme.readPressure() /100.0f)/68.9476;
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA)*3.28084;
  hum = bme.readHumidity();
// make void for displaying ethernet status on oled
button1.tick();
if (startState == true){
  oled.setBrightness(255);
  subMenu = false;
  smartMenu = false; 
  switch(i){   
    case 0:
    Menu();
    Select1();
      break;
    case 1:
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
             if (temp >= 70){
              if (star == false){
                sol();
                star = true;
             }
             } 
             if(temp <= 69){
              if(frost == false){
                flake();
                frost = true;   
              }
             }
             bmeValT(temp);
              break;             
            case 2:
             if (thicc == false){
              weights();
              thicc = true;
             }
              bmeValP(pres);
            Serial.println("SM 2");
              break;
            case 3:
              bmeValA(alt);
              Serial.println("SM 3");
              break;
            case 4:
             if (drip == false){
              moisture();
              drip = true;
              } 
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
          SmartStatMenu();
          SelectSM();
         break;
          case 1:
          
          if (bars == false){
            SCon();
            bars = true;
          }
          SSMyes();
          smartControl = true;
          hueState = true;
          wemoState = true;
          delay(3000);
          s=0;
          i=0;
          oled.clearDisplay();
         break;
          case 2:
           
           if(nobars == false){
            SCoff();
            nobars = true;
           }
           SSMno();
           smartControl = false;
           delay(3000);
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
      if (zap == false){
        PWR();
        zap = true;       
      }
      powerMenu();
      delay(3000);
      shutDown();
      Serial.println("four");
      break;  
  }
  Serial.print(n);
 smartStateLed();
// wemoSet();
// hueSet();
 NeoRing();
}
if(startState==false){ // leaving the SRC in standby mode, awaiting input
  standby();
}
}

void click1(){ // calling click function from one button library. used to select menus and menu options.
  buttonState =! buttonState;
  startState = true;
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
     if (star == true){ 
       star = false;
     }
     if (frost == true){
      frost = false;
     }
     if(drip == true){
      drip = false;
     }
     if(thicc == true){
      thicc = false;
     }
     if(zap == true){
      zap = false;
     }
     if(bars == true){
      bars = false;
     }
     if(nobars == true){
      nobars = false;
     }
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
  oled.setTextXY(0,5);
  oled.putString("*F");
}
void bmeValP(float ppres){ // function to display pressure
  oled.setTextXY(0,0);
  oled.putString(float(ppres));
  oled.setTextXY(0,6);
  oled.putString("hPa");
}
void bmeValA(float palt){  // function to display altitude
  oled.setTextXY(0,0);
  oled.putString(float(palt));
  oled.setTextXY(0,8);
  oled.putString("ft");
}
void bmeValH(float phum){ //function to display humidity
  oled.setTextXY(0,0);
  oled.putString(float(phum));
  oled.setTextXY(0,5);
  oled.putString("%");
}
void standby(){ // function for leaving SRC in standby 
  oled.setBrightness(20);
  oled.setTextXY(2,5);
  oled.putString("SRC in");
  oled.setTextXY(3,2);
  oled.putString("standby mode");
  
}
void shutDown(){ // function for returning all initial values and turning off screen.
  startState = false;
  hueState = false;
  wemoState = false;
  smartControl = false;
  oled.clearDisplay();
  enc.write(0);
  s=0;
  n=0;
  i=0;
  // dont forget writing servo back to 0
  // and the leds off 
}
void wemoSet(){ // function for smart control to use the wemo pins. 
  int wemo; 
  if(wemoState == true){
   if(temp<=69){
    wemo = 1;
   switchON(wemo);
   if(temp>69){
   switchOFF(wemo);
    }
   }
   if(temp>=70){
    wemo = 2;
   switchON(wemo);
   if(temp<70){
   switchOFF(wemo);
    }
   }  
  }
  else if(wemoState == false){ // check this code on monday
    wemo = 1;
    switchOFF(wemo);
    delay(10);
    wemo = 2;
    switchOFF(wemo);
  }
}
void hueSet(){
  if( hueState == true){
  onoff =! onoff;
  }
  if(onoff==true){
  activated=true;
  bulb = 2;
  if(smartControl == true){
  setHue(bulb, activated,colorShift[showTemp],luminosity());
  }
  if(smartControl == false){
  setHue(bulb, activated,colorShift[showTemp],250);
  } 
}
}

void NeoRing(){ // function for using NeoPixel ring. Also uses smart control.
    if (startState == true){
    showTemp = temp;
    showTemp = map(showTemp, 0, 100, 0, 12);
    if (smartControl == false){
    pixel.clear();
    pixel.setPixelColor(showTemp,colorShift[showTemp]);
    pixel.setBrightness(100);
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
    if(startState == false){
      pixel.fill(0x000000, 0, 12);
      pixel.show();
    }
}

unsigned int luminosity(){
  int pResistor = 14; 
  int pSenseVal;
  int analogVal;
  int bitSenseVal;
  pSenseVal = analogRead(pResistor);
  bitSenseVal = map(pSenseVal, 100, 1023, 1, 255);  // once value gets too low it goes back to 1023
  return bitSenseVal;
}
