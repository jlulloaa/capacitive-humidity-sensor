/***************************************************
 This example reads Capacitive Soil Moisture Sensor.

 Created 2015-10-21
 By berinie Chen <bernie.chen@dfrobot.com>

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here: https://www.dfrobot.com/wiki/index.php?title=Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 2.This code is tested on Arduino Uno.
 3.Sensor is connect to Analog 0 port.
 ****************************************************/
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

LiquidCrystal lcd(RS, E, DB04, DB05, DB06, DB07);

// Add control to switch on and off the lcd (to save battery)
const int BUTTON_PIN = 5;  // the number of the pushbutton pin
const int LCD_PIN = 6;    // the number of the LCD "A" pin (LED+)
// initialise the ButtonState
int buttonState = 0;  // variable for reading the pushbutton status

// Add LED alerting low humidity
#define LED 7 //connect LED to digital pin7

// Power through laptop USB
// const float AirValue = 815.0;   //When powerup through the USB (laptop)
// const float WaterValue = 445.0;  //When powerup through the power cord (elec socket)

// Power through electrical socket
const float AirValue = 805.0;   //When powerup through the power cord (elec socket)
const float WaterValue = 435.0;  //When powerup through the power cord (elec socket)

int setT = 3000; 
int T = setT; // sampling interval (milli second)

int soilMoistureValue = 0;
float m = 100.0 / (WaterValue - AirValue);
float n = -1.0 * m * AirValue;
float pcRelMoistureValue = 0.0;
float moistureThreshold = 75.0; // Threshold to set the LED on (i.e. require water)

// Text buffer
char top_buffer [18]; // a few bytes larger than your LCD line
char bottom_buffer [18]; // a few bytes larger than your LCD line

void setup() {
  // initialize the pushbutton pin as an input:
  // https://roboticsbackend.com/arduino-push-button-tutorial/
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // initialize the LCD Switch pin as an output:
  pinMode(LCD_PIN, OUTPUT);
  // Initial state of the screen is ON:
  digitalWrite(LCD_PIN, HIGH);
  // Add button-press indicator with the built-in led
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the digital LED as an output.
   pinMode(LED, OUTPUT);     
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hola!");
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  // Read the humidity sensor and gets a percentage equivalent
  soilMoistureValue = (float) analogRead(A0);  //put Sensor insert into soil
  pcRelMoistureValue = soilMoistureValue * m + n;
  Serial.println(pcRelMoistureValue);

  if (pcRelMoistureValue <= moistureThreshold) {
      digitalWrite(LED, HIGH);   // set the LED on
      sprintf(top_buffer, "I'm thirsty :(");
      sprintf(bottom_buffer, "Humedad = %3d.%1d%%", (int)pcRelMoistureValue,int(pcRelMoistureValue*10)%10);   
  } else {
      digitalWrite(LED, LOW);   // set the LED off
      sprintf(top_buffer, "I'm happy :)  ");
      sprintf(bottom_buffer, "Humedad = %3d.%1d%%", (int)pcRelMoistureValue,int(pcRelMoistureValue*10)%10);
  }

  // Ensure the screen is off by default:
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LCD_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.print(top_buffer);
    lcd.setCursor(0, 1);
    lcd.print(bottom_buffer);
    // lcd.print(pcRelMoistureValue);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LCD_PIN, LOW);
  } 

  delay(T);
}
