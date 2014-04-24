/*
 *  Cheerlights Ethernet - Dave Jacoby
 *
 *  Using an Ethernet Shield to connect to Cheerlights and set the RGB LED light
 *
 *  http://api.thingspeak.com/channels/1417/field/1/last.txt
 *
 * Sketch to set control of an RGB LED
 *
 * Black wire connecting 5v to LED pin 2
 * Red wire (red color) connecting A pin 1 to LED 1
 * Green wire (green color) connecting A pin 2 to LED 3
 * Blue wire (blue color) connecting A pin 3 to LED 4
 */

#include <SPI.h>
#include <Ethernet.h>

const int redPin = 3 ;
const int greenPin = 5 ;
const int bluePin = 6 ;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Arduino's MAC
IPAddress ip(192, 168, 1, 177); // Arduino's Address
char server[] = "api.thingspeak.com";
EthernetClient client;

int led = 0 ;
int delay_length = 6000 ;

// Cobble together these with ascii. 
char blu[4] = {10, 98, 108, 117} ; 
char cya[4] = {10, 99, 121, 97} ;
char dar[4] = {10, 100, 97, 114} ;
char gre[4] = {10, 103, 114, 101} ;
char mag[4] = {10, 109, 97, 103} ; 
char ora[4] = {10, 111, 114, 97} ; 
char pur[4] = {10, 112, 117, 114} ; 
char red[4] = {10, 114, 101, 100} ; 
char war[4] = {10, 119, 97, 114} ; 
char whi[4] = {10, 119, 104, 115} ; 
char yel[4] = {10, 121, 101, 108} ; 

// ======================================================================
void setup() {
  Serial.begin(9600);
  delay(100) ;

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  // give the Ethernet shield a second to initialize:
  Serial.println("connecting...");
}

// ======================================================================
void loop() {
  get_lights( server ) ;
  delay( delay_length ) ;
}

// ======================================================================
void get_lights( char server[] ) {
  Serial.print( server ) ;
  Serial.println( " ------------------------------" ) ;
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /channels/1417/field/1/last.txt HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
    delay( 500 ) ; // delay to make sure client is available

    if (client.available()) {
      char matchbuf[4] ;
      char newline[] = {13, 10} ;
      while (client.available() > 0) {
        matchbuf[0] = matchbuf[1];
        matchbuf[1] = matchbuf[2];
        matchbuf[2] = matchbuf[3];
        matchbuf[3] = client.read();

        if ( strcmp(blu, matchbuf) == 10 ) {
          Serial.println( "Blue" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(blu, matchbuf) ) ;
          Serial.println( blu ) ;
          c_blue() ;
        }
        else if ( strcmp(cya, matchbuf) == 10 ) {
          Serial.println( "Cyan" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(blu, matchbuf) ) ;
          Serial.println( cya ) ;
          c_cyan() ;
        }
        else if ( strcmp(dar, matchbuf) == 10 ) {
          Serial.println( "Dark" ) ;
          c_dark() ;
        }
        else if ( strcmp(gre, matchbuf) == 10 ) {
          Serial.println( "Green" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(blu, matchbuf) ) ;
          Serial.println( gre ) ;
          c_green() ;
        }
        else if ( strcmp(mag, matchbuf) == 10 ) {
          Serial.println( "Magenta" ) ;
          c_magenta() ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(blu, matchbuf) ) ;
          Serial.println( mag ) ;
        }
        else if ( strcmp(ora, matchbuf) == 10 ) {
          Serial.println( "Orange" ) ;
          c_orange() ;
        }
        else if ( strcmp(pur, matchbuf) == 10 ) {
          Serial.println( "Purple" ) ;
          c_purple() ;
        }
        else if ( strcmp(red, matchbuf) == 10 ) {
          Serial.println( "Red" ) ;
          c_red() ;
        }
        else if ( strcmp(war, matchbuf) == 10 ) {
          Serial.println( "Warmwhite" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(war, matchbuf) ) ;
          Serial.println( war ) ;
          c_warmwhite() ;
        }
        else if ( strcmp(whi, matchbuf) == 10 ) {
          Serial.println( "White" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(blu, matchbuf) ) ;
          Serial.println( whi ) ;
          c_white() ;
        }
        else if ( strcmp(yel, matchbuf) == 10 ) {
          Serial.println( "Yellow" ) ;
          Serial.println( matchbuf ) ;
          Serial.println( strcmp(yel, matchbuf) ) ;
          Serial.println( yel ) ;
          c_yellow() ;
        }
      }
    Serial.println( "--------------------" ) ;
    }
    else {
      Serial.println();
      Serial.println("disconnecting.");
    }
  }
  else {
    Serial.println("connection failed");
  }
  client.stop() ;
}

// ======================================================================
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  Serial.print( "\t" ) ;
  Serial.print( red ) ;
  Serial.print( "\t" ) ;
  Serial.print( green ) ;
  Serial.print( "\t" ) ;
  Serial.println( blue ) ;
  analogWrite( redPin   , red   ) ;
  analogWrite( greenPin , green ) ;
  analogWrite( bluePin  , blue  ) ;
}

// ======================================================================
void c_red()       {
  setColourRgb(   0, 255, 255 ) ;
}

// ======================================================================
void c_green()     {
  setColourRgb( 255,   0, 255 ) ;
}

// ======================================================================
void c_blue()      {
  setColourRgb( 255, 255,   0 ) ;
}

// ======================================================================
void c_cyan()      {
  setColourRgb( 255,   0,   0 ) ;
}

// ======================================================================
void c_white()     {
  setColourRgb(   0,   0,   0 ) ;
}

// ======================================================================
void c_warmwhite() {
  setColourRgb(   0,  32,  32 ) ;
}

// ======================================================================
void c_purple()    {
  setColourRgb( 128, 255, 128 ) ;
}

// ======================================================================
void c_magenta()   {
  setColourRgb(   0, 255,   0 ) ;
}

// ======================================================================
void c_yellow()    {
  setColourRgb(   0,   0, 255 ) ;
}

// ======================================================================
void c_orange()    {
  setColourRgb(   0, 165, 255 ) ;
}

// ======================================================================
void c_dark()      {
  setColourRgb( 255, 255, 255 ) ;
}


