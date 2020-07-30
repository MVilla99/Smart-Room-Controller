#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
//#include <SD.h>
#include <SPI.h>
//#include <color.h>
#include <Encoder.h>
#include <colorshift.h>
  #define SEALEVELPRESSURE_HPA (1013.25)
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 32
    float temp;
    float pres;
    float hum;
    float alt;
    int showTemp;
    int colorShift[] = {blue4, blue3 ,blue2 ,blue1 ,blue0 ,mid1 ,mid2 ,red0 ,red1 ,red2 ,red3 ,red4 };
Adafruit_NeoPixel pixel(12, 20, NEO_GRB + NEO_KHZ800); // dont forget, change pin.  
Adafruit_SSD1306 dis1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_BME280 bme;
Encoder enc(15,16);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);
Wire.begin();
pixel.begin();
pixel.show();
  unsigned status;
  status = bme.begin(0x76);
  if(!status){
    Serial.printf("BME FAILED\n");
  }
    else{
      Serial.println("  SENSOR ENGAGED ");
      delay(500);
    }
  if(!dis1.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.printf("SSD1306 allocation failed\n");
  }
    dis1.clearDisplay();
    dis1.display();
//  if(!SD.begin(chipSelect)){
//    Serial.println("CARD FAILED");
  }
//    else{
//      Serial.println("  SD INITIALIZED  ");
//    }
//}

void loop() {
  // put your main code here, to run repeatedly:
temp = (bme.readTemperature() * 9/5)+32; // map shifttemp(0,100,0,12) for neopixel temp change
pres = (bme.readPressure() /100.0f)/68.9476;
alt = bme.readAltitude(SEALEVELPRESSURE_HPA)*3.28084;
hum = bme.readHumidity();
 // sensValO(temp,pres,alt,hum);
showTemp = temp;
showTemp = map(showTemp, 0, 100, 0, 12);
pixel.setPixelColor(showTemp,colorShift[showTemp]); 
//pixel.fill(colorShift[showTemp],0,showTemp);
pixel.setBrightness(30);
pixel.show();
Serial.print(showTemp);
Serial.println(temp);
}
/* Cshift();
}
void sensValO(float Otemp, float Opres, float Oalt, float Ohum){
  dis1.clearDisplay();
  dis1.setTextSize(1);
  dis1.setTextColor(SSD1306_WHITE);
  dis1.setCursor(0,0);
  dis1.printf("temp= %0.3f degrees  approx. alt= %0.1f m\n", Otemp,Oalt);
  dis1.setCursor(0,17);
  dis1.printf("pressure= %0.3f hPa  humidity= %0.2f %\n", Opres,Ohum);
  dis1.display();
  dis1.startscrollright(0x00, 0x0F);
  delay(10000);
  dis1.stopscroll();
  dis1.clearDisplay();
  dis1.setTextSize(1);
  dis1.setTextColor(SSD1306_WHITE);
  dis1.setCursor(5,5);
  dis1.printf("READING NEW DATA\n");
  dis1.display();
  delay(500);
}`*/

/*
void Cshift(){
  int ticks = enc.read();
  int Nticks = (ticks/8);
    pixel.clear();
    pixel.setPixelColor(Nticks, colorShift[Nticks]);
    pixel.setBrightness(80);
    pixel.show();
    Serial.println(Nticks);
  } */
