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

#include <String.h>
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
int delay_length = 1000 ;

// Cobble together these with ascii.
char blu[5] = {10, 98, 108, 117 , 0} ;
char cya[5] = {10, 99, 121, 97 , 0} ;
char dar[5] = {10, 100, 97, 114 , 0} ;
char gre[5] = {10, 103, 114, 101 , 0} ;
char mag[5] = {10, 109, 97, 103 , 0} ;
char ora[5] = {10, 111, 114, 97 , 0} ;
char pur[5] = {10, 112, 117, 114 , 0} ;
char red[5] = {10, 114, 101, 100 , 0} ;
char war[5] = {10, 119, 97, 114 , 0} ;
char whi[5] = {10, 119, 104, 115 , 0} ;
char yel[5] = {10, 121, 101, 108 , 0} ;

String blue = blu ;
String cyan = cya ;
String dark = dar ;
String green = gre ;
String magenta = mag ;
String orange = ora ;
String purple = pur ;
String redd = red ;
String warmwhite = war ;
String white = whi ;
String yellow = yel ;

//String dark = dar ;
//char crlf[4] = { 13 , 10 , 13 , 10 } ;

//String newString = oldString;
// ================================================================================
void setup() {
  Serial.begin(9600);
  delay(100) ;
  Serial.println( "Starting" ) ;
  c_white() ;

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
    c_red() ;
  }

  // give the Ethernet shield a second to initialize:
  Serial.println("connecting...");
}

// ================================================================================
void loop() {
  get_lights( server ) ;
  delay( delay_length ) ;
}

// ================================================================================
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
      char matchbuf[5] ;
      char newline[] = {13, 10} ;
      while (client.available() > 0) {
        matchbuf[0] = matchbuf[1];
        matchbuf[1] = matchbuf[2];
        matchbuf[2] = matchbuf[3];
        matchbuf[3] = client.read();
        matchbuf[4] = 0 ;
        String matchstr = matchbuf ;

        if ( matchstr.equals( blue ) ) {
          Serial.println( "BLUE" ) ;
          c_blue() ;
        }
        if ( matchstr.equals( cyan ) ) {
          Serial.println( "CYAN" ) ;
          c_cyan() ;
        }
        if ( matchstr.equals( dark ) ) {
          Serial.println( "DARK" ) ;
          c_dark() ;
        }
        if ( matchstr.equals( green ) ) {
          Serial.println( "GREEN" ) ;
          c_green() ;
        }
        if ( matchstr.equals( magenta ) ) {
          Serial.println( "MAGENTA" ) ;
          c_magenta() ;
        }
        if ( matchstr.equals( purple ) ) {
          Serial.println( "PURPLE" ) ;
          c_purple() ;
        }
        if ( matchstr.equals( redd ) ) {
          Serial.println( "Red" ) ;
          c_red() ;
        }
        if ( matchstr.equals( warmwhite ) ) {
          Serial.println( "WARM WHITE" ) ;
          c_warmwhite() ;
        }
        if ( matchstr.equals( white ) ) {
          Serial.println( "WHITE" ) ;
          c_white() ;
        }
        if ( matchstr.equals( yellow ) ) {
          Serial.println( "YELLOW" ) ;
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

// ================================================================================
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

// ================================================================================
void c_red()       {
  setColourRgb(   0, 255, 255 ) ;
}

// ================================================================================
void c_green()     {
  setColourRgb( 255,   0, 255 ) ;
}

// ================================================================================
void c_blue()      {
  setColourRgb( 255, 255,   0 ) ;
}

// ================================================================================
void c_cyan()      {
  setColourRgb( 255,   0,   0 ) ;
}

// ================================================================================
void c_white()     {
  setColourRgb(   0,   0,   0 ) ;
}

// ================================================================================
void c_warmwhite() {
  setColourRgb(   0,  32,  32 ) ;
}

// ================================================================================
void c_purple()    {
  setColourRgb( 128, 255, 128 ) ;
}

// ================================================================================
void c_magenta()   {
  setColourRgb(   0, 255,   0 ) ;
}

// ================================================================================
void c_yellow()    {
  setColourRgb(   0,   0, 255 ) ;
}

// ================================================================================
void c_orange()    {
  setColourRgb(   0, 165, 255 ) ;
}

// ================================================================================
void c_dark()      {
  setColourRgb( 255, 255, 255 ) ;
}


