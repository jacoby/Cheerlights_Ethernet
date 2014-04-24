 /*
  * Cheerlights Ethernet, a program that connects directly to the Cheerlights
  * API to turn a common-anode RGB LED to different colors
  */

#include <SPI.h>
#include <Ethernet.h>

const int redPin = 1 ;
const int greenPin = 2 ;
const int bluePin = 3 ;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "api.thingspeak.com";


void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.flush();
  delay(100);
  pinMode( redPin , OUTPUT ) ;
  pinMode( greenPin , OUTPUT ) ;
  pinMode( bluePin , OUTPUT ) ;

}

void loop() {
  // put your main code here, to run repeatedly:

}


// --------------------------------------------------
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  Serial.print( red ) ;
  Serial.print( "\t" ) ;
  Serial.print( green ) ;
  Serial.print( "\t" ) ;
  Serial.println( blue ) ;
  analogWrite( redPin   , red   ) ;
  analogWrite( greenPin , green ) ;
  analogWrite( bluePin  , blue  ) ;
}

void c_red()       {
  setColourRgb(   0, 255, 255 ) ;
}
void c_green()     {
  setColourRgb( 255,   0, 255 ) ;
}
void c_blue()      {
  setColourRgb( 255, 255,   0 ) ;
}
void c_cyan()      {
  setColourRgb( 255,   0,   0 ) ;
}
void c_white()     {
  setColourRgb(   0,   0,   0 ) ;
}
void c_warmwhite() {
  setColourRgb(   0,  32,  32 ) ;
}
void c_purple()    {
  setColourRgb( 128, 255, 128 ) ;
}
void c_magenta()   {
  setColourRgb(   0, 255,   0 ) ;
}
void c_yellow()    {
  setColourRgb(   0,   0, 255 ) ;
}
void c_orange()    {
  setColourRgb(   0, 165, 255 ) ;
}
void c_dark()      {
  setColourRgb( 255, 255, 255 ) ;
}



