// testing for one button switch case
#include <OneButton.h>
#include <Encoder.h>
Encoder enc(15,16);
OneButton button1(17,false);
bool buttonState = HIGH;
int i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);
button1.attachClick(click1);
button1.setClickTicks(250);
button1.setPressTicks(2000);
}

void loop() {
button1.tick();
  switch(i){
    case 1:  // use enc "ticks" mapped to each S-C statement and the button will act as the select
      Serial.println("zero");
      break;
    case 2:
      Serial.println("one");
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
  i++;
  if(i>4){
    i=0;
  }

//  i = (enc.read/24)
 
}
