// testing for one button switch case
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <OneButton.h>
#include <Encoder.h>
#include <menuSelect.h>
  #define imageWidth 128
  #define imageHeight 64
//Encoder enc(15,16);
OneButton button1(17,false);
bool buttonState = HIGH;
int i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);
Wire.begin();
oled.init();
oled.clearDisplay();
button1.attachClick(click1);
button1.setClickTicks(250);
button1.setPressTicks(2000);
Menu(); // when bitmap clears the screen it clears Menu
}

void loop() {
button1.tick();
 //Menu(); //setup
 //Select();

  switch(i){
    case 0:
    Menu();
    Select();
      break;
    case 1:  // use enc "ticks" mapped to each S-C statement and the button will act as the select
      Serial.println("zero");
      break;
    case 2:
      Serial.println("one");
      Menu3();
      delay(1000);
      break;
    case 3:
      Serial.println("two");
      break;
    case 4:
      Serial.println("three");
      break;  
  }

}
void click1(){
  buttonState =! buttonState;
  i = (enc.read()/24);

 
}
