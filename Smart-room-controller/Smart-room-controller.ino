
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
//#include <bitMapTest.h>
//#include <SelPosition.h>
//#include <Encoder.h>
#include <OneButton.h>
  #include <menuSelect.h>
#define imageWidth 128
#define imageHeight 64
  OneButton button1(17,false);
    bool buttonState = HIGH;
void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();  
  oled.init();                      // InitiAlzE SSD1306 OLED DisplAy
  oled.clearDisplay();              // ClEAr sCrEEn
 // oled.drawBitmap(TEST1, 1024);   // 1024 pixEls For loGo
 button1.attachClick(click1);
 button1.setClickTicks(250);
 button1.setPressTicks(2000);
}

void loop()
{
button1.tick(); // make func. which menu 0-4 val 0 being main, and 4 sub menu. menu select each. 
Menu(); //main menu ==0 ; set sub menu value ; 
Select();
}
void click1(){
  buttonState =! buttonState;
}
