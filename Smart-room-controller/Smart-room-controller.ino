// testing for one button switch case
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <OneButton.h>
#include <Encoder.h>
  Encoder enc(15,16);
#include <interfaceMenu.h>
#include <interfaceSelect.h>
#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
  #define imageWidth 128
  #define imageHeight 64
  #define SEALEVELPRESSURE_HPA (1013.25)
    Adafruit_BME280 bme;   
    float temp;
    float pres;
    float hum;
    float alt;
int encButton = 17;
OneButton button1(encButton,false); // try with normal button 
bool buttonState = HIGH;
bool DBclick = LOW;
int i;

void setup() {
  // put your setup code here, to run once:
//pinMode(encButton, INPUT);
Serial.begin(9600);
Ethernet.begin(mac);
while(!Serial);
Wire.begin();
oled.init();
oled.clearDisplay();
  unsigned status;
  status = bme.begin(0x76);
  
button1.attachClick(click1);
button1.attachDoubleClick(doubleclick1);
button1.setClickTicks(250);
button1.setPressTicks(2000);
  temp = (bme.readTemperature() * 9/5)+32;
  pres = (bme.readPressure() /100.0f)/68.9476;
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA)*3.28084;
  hum = bme.readHumidity();
}

void loop() {
button1.tick();
 //Menu(); //setup
 //Select();

  switch(i){
    case 0:
    Menu();
    Select1();
      break;
    case 1:  // use enc "ticks" mapped to each S-C statement and the button will act as the select
      Serial.println("one");
      Menu2();
      Select2();
      break;
    case 2:
      Serial.println("two");
      Menu3();
      Select3();
      //delay(1000);
      break;
    case 3:
      Serial.println("three");
      //ethernetStat();
      bmeVal(temp);
      Select4();
      break;
    case 4:
      Serial.println("four");
      break;  
  }

}
void click1(){
  buttonState =! buttonState;
  i = (enc.read()/24); 
}
void doubleclick1(){
  DBclick =! DBclick;
  oled.clearDisplay();
  //enc.write(0);
  //oled.clearDisplay();
  i=0;
}
void bmeVal(float ptemp){
  //oled.clearDisplay();
  oled.setTextXY(0,0);
  oled.putString(float(ptemp));
}
void ethernetStat(){
Serial.print("my IP address: ");
  for(byte myByte = 0; myByte < 4; myByte++){
    Serial.print(Ethernet.localIP()[myByte],DEC);
    Serial.print(".");    
  }  
}
