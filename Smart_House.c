
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int left_sensor = 6;
int right_sensor = 7;
int alarm_pin = 8;
 

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(alarm_pin, OUTPUT);
  
}

void loop() {
  
  float left_time, right_time, left_dist, right_dist;
  
  // Test proper functionality of the ultrasonic sensor
  // Left House Sensor
  pinMode(left_sensor, OUTPUT);
  digitalWrite(left_sensor, LOW);
  delayMicroseconds(2);
  digitalWrite(left_sensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(left_sensor, LOW);
  
  // use left house sensor to sense distance between obstacle when pulse is HIGH
  pinMode(left_sensor, INPUT);
  left_time = pulseIn(left_sensor, HIGH);
  
  // Convert time to distance
  left_dist = microsecondsToCentimeters(left_time);
  
  delay(100);
  
  // Right House Sensor
  pinMode(right_sensor, OUTPUT);
  digitalWrite(right_sensor, LOW);
  delayMicroseconds(2);
  digitalWrite(right_sensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(right_sensor, LOW);
  
  // use right house sensor to sense distance between obstacle when pulse is HIGH
  pinMode(right_sensor, INPUT);
  right_time = pulseIn(right_sensor, HIGH);
  
  // Convert time to distance
  right_dist = microsecondsToCentimeters(right_time);
  
  delay(100);

  // Check if distance and activate alarm accordinglys
  if (left_dist < 150) {
  	// Set Alarm on for Left Side breach
    digitalWrite(alarm_pin,HIGH);
    lcd.setCursor(0,0);
    lcd.print("Stranger On:  ");
    lcd.setCursor(0,1);           
    lcd.print("Left_Side: "); 
    lcd.print(left_dist);

  } else if (right_dist < 150) {
  	// Set Alarm on for Right Side breach
    digitalWrite(alarm_pin,HIGH);
    lcd.setCursor(0,0);
    lcd.print("Stranger On: ");
    lcd.setCursor(0,1);           
    lcd.print("Right_Side: ");
    lcd.print(right_dist);
  } 
  else if (left_dist >= 150) {
  	digitalWrite(alarm_pin,LOW);
    lcd.clear();
	lcd.setCursor(0,0);
    lcd.print("House is Safe");
    lcd.print(left_dist);
  } 
  else if (right_dist >= 150) {
  	digitalWrite(alarm_pin,LOW);
    lcd.clear();
	lcd.setCursor(0,0);
    lcd.print("House is Safe");
    lcd.print(right_dist);
  }
  delay(100);
}
 

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
