/* written by mauricio villa */
// needs ACROBOTIC_SSD1306 initialization in setup before use.

void Menu(){ // main menu for displaying all functions for smart room controller
  oled.setTextXY(0,0);
  oled.putString("BME readings:");
  oled.setTextXY(2,0);
  oled.putString("Smart Control:");
  oled.setTextXY(4,0);
  oled.putString("User Manual:");
  oled.setTextXY(6,0);
  oled.putString("Power");
}

void bmeMenu(){ // menu for selectiong which bme reading to display
oled.setTextXY(0,0);
oled.putString("temperature");
oled.setTextXY(2,0);
oled.putString("pressure");
oled.setTextXY(4,0);
oled.putString("altitude");
oled.setTextXY(6,0);
oled.putString("humidity");
}

void SmartStatMenu(){
oled.setTextXY(4,0);
oled.putString("Yes");
oled.setTextXY(6,0);
oled.putString("No");
}

void SSMyes(){ // display message for enabling smart control
oled.setTextXY(0,0);
oled.putString("Thank you for");
oled.setTextXY(1,0);
oled.putString("enabling smart");
oled.setTextXY(2,0);
oled.putString("room control");
oled.setTextXY(5,0);
oled.putString("hold button to");
oled.setTextXY(6,0);
oled.putString("disable control");
}

void SSMno(){ //display message for turning off smart control 
oled.setTextXY(0,0);
oled.putString("Smart controller");
oled.setTextXY(1,0);
oled.putString("set to off");

}

void userManual(){ //description of what the button does
oled.setTextXY(0,0);
oled.putString("push button to");
oled.setTextXY(1,0);
oled.putString("select option on");
oled.setTextXY(2,0);
oled.putString("scroll menu");
oled.setTextXY(3,0);
oled.putString("----------------");
oled.setTextXY(4,0);
oled.putString("double click to");
oled.setTextXY(5,0);
oled.putString("return to the");
oled.setTextXY(6,0);
oled.putString("main menu");
}

void powerSel(){ // menu for switching the smart room controller off
oled.setTextXY(0,0);
oled.putString("switch SRC off?");
oled.setTextXY(4,0);
oled.putString("Yes --");
oled.setTextXY(6,0);
oled.putString("No --");
// rewrite all and put "to turn off, press and hold button. and assign long press to return all 
}