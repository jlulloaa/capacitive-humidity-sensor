// JU - added support to the LCD
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
const int DB07 = 8;
const int DB06 = 9;
const int DB05 = 10;
const int DB04 = 11;
const int E = 12;
const int RS = 13;

const int LCD_PIN = 6;    // the number of the LCD "A" pin (LED+)

LiquidCrystal lcd(RS, E, DB04, DB05, DB06, DB07);
int T = 1000; // sampling interval

int moistureRead = 0;

void setup() {
  // initialize the LCD Switch pin as an output:
  pinMode(LCD_PIN, OUTPUT);  
  // Set the state of the screen to ON:
  digitalWrite(LCD_PIN, HIGH);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Humidity Read:");
 // initialise Serial monitor
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
}

void loop() {
  moistureRead = analogRead(0); //connect sensor to Analog 0
  lcd.setCursor(0, 1);
  lcd.print(moistureRead);
  Serial.println(moistureRead); //print the value to serial port
  delay(T);
}