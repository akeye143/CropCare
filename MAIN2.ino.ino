#include <Servo.h> //servo library
#include <Wire.h>
#include <rgb_lcd.h>
 
Servo ultraServo; // create servo object to control servo
Servo soilServo; //create servo to control soil sensor movement
rgb_lcd lcd;
int Echo = A3;
int Trig = A2;
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6
#define carSpeed 50
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
int Moisture_signal = A0; // Pin for soil moisture sensor signal
//const int ServoSensor = 13;// Pin for providing power to the sensor
const int PowerPin = 12; // use this digital pin for power source
//pins for the servo motor that contril its movemnents
int portIN1 = 2;
int portIN2 = 4;
int portIN3 = 5;
int portIN4 = 6;
int i = 0;
int full_rotation = 510;
int condition = false;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
 
void forward(){
analogWrite(ENA, carSpeed);
analogWrite(ENB, carSpeed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
Serial.println("Forward");
}
void back() {
analogWrite(ENA, carSpeed);
analogWrite(ENB, carSpeed);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
Serial.println("Back");
}
void left() {
analogWrite(ENA, carSpeed);
analogWrite(ENB, carSpeed);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
Serial.println("Left");
}
void right() {
analogWrite(ENA, carSpeed);
analogWrite(ENB, carSpeed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
Serial.println("Right");
}
 
void stop() {
digitalWrite(ENA, LOW);
digitalWrite(ENB, LOW);
Serial.println("Stop!");
}
//Ultrasonic distance measurement Sub function
int getDistance() {
digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
return (int)pulseIn(Echo, HIGH) / 58;
}
 
void detect_moisture(){
  digitalWrite(PowerPin,HIGH);
  delay(1200);
  int Moisture = analogRead(Moisture_signal);
  digitalWrite(PowerPin, LOW);
  Serial.print("Soil Moisture Level: ");
  lcd.setCursor(0, 0);
  lcd.print("Moisture Level:");
  lcd.setCursor(0, 1);
  if (Moisture >= 900) {
    lcd.print("Soil is too dry");
    Serial.println();
  }
  else if (Moisture >= 500){
    lcd.print("Soil is perfect");
    Serial.println();
    //condition =  true;
  }
  else {
    lcd.print("Soil is too wet");
    Serial.print(Moisture);
    Serial.println();
  }
  delay(3000);
}
 
void dropServo(){
  //digitalWrite(ServoSensor, HIGH);
   soilServo.write(180); //moves servo 150 degrees'
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("   Stop Check   ");
   lcd.setCursor(0, 1);
   lcd.print("Soil Moisture Lvl");
   delay(5000);
   detect_moisture();
   //digitalWrite(ServoSensor,LOW);
   delay(1000);
   soilServo.write(0); // servoc moves back to intial position 
   delay(1000);
}
 
//rotates thhe stepper motor clockwise 
void stepperClockwise(int delays = 1500){
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
}
 
//rotates thhe stepper motor anti-clockwise 
void stepperAnticlockwise(int delays = 1500){
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,LOW);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,HIGH);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,LOW);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,HIGH);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
  digitalWrite(portIN1,LOW);
  digitalWrite(portIN2,LOW);
  digitalWrite(portIN3,HIGH);
  digitalWrite(portIN4,HIGH);
  delayMicroseconds(delays);
}
 
void rotate_clockwise(float angle){
  int rotation = full_rotation*angle;
  for(i=rotation;i>=1;i--)
  {
    stepperClockwise(1500);   
  }
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Dispense    ");
  lcd.setCursor(0, 1);
  lcd.print("    The Seeds    ");
  delay(200);
  lcd.clear();
}
 
void rotate_anticlockwise(float angle){
  int rotation = full_rotation*angle;
  for(i=rotation;i>=1;i--)
  {
    stepperAnticlockwise(1500);  
  }
}
 
void moveShortDistances(int duration){
  long startTime = millis();
  //forward();
  while(millis() - startTime < duration){
    if (condition == false){
      forward();
      rotate_clockwise(1);  
    }
  Serial.print("MOVED FOR: ");
  Serial.println(startTime);
  stop(); 
  }
}
void setup() {
ultraServo.attach(3); // attach servo on pin 3 to servo object
soilServo.attach(10); // attaches servo to pin 12
Serial.begin(9600);
pinMode(Echo, INPUT);
pinMode(Trig, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(PowerPin, OUTPUT); // turns servo motor on
digitalWrite(PowerPin, LOW); //turns servo motor off
//pinMode(ServoSensor, OUTPUT);
//digitalWrite(ServoSensor, LOW);
pinMode(portIN1,OUTPUT);
pinMode(portIN2,OUTPUT);
pinMode(portIN3,OUTPUT);
pinMode(portIN4,OUTPUT);
lcd.begin(16,2);
lcd.setRGB(colorR, colorG, colorB);
lcd.print("     Hello!");
lcd.setCursor(0, 1);
lcd.print("I am CropCare :)");
delay(2000);
lcd.clear();
 
stop();
}
void loop() {  
ultraServo.write(90); //setservo position according to scaled value
delay(500);
middleDistance = getDistance();
if(middleDistance <= 50) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("     CAUTION!   ");
   lcd.setCursor(0, 1);
   lcd.print("Object Detected ");
   stop();
   delay(500);
   ultraServo.write(10);
   delay(1000);
   rightDistance = getDistance();
   delay(500);
   ultraServo.write(90);
   delay(1000);
   ultraServo.write(180);
   delay(1000);
   leftDistance = getDistance();
   delay(500);
   ultraServo.write(90);
   delay(1000);
   if(rightDistance > leftDistance) {
   lcd.clear();
   lcd.setCursor(0, 1);
   lcd.print("  Turning Right  ");
   delay(200);
   right();
   delay(360);
   stop();
   delay(2000);
   }
   else if(rightDistance < leftDistance) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("  Turning Left  ");
    delay(200);
    left();
    delay(360);
    stop();
    delay(2000);
   }
   else if((rightDistance <= 20) || (leftDistance <= 20)) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" Reversing Back ");
    delay(200);
    back();
    delay(180);
    stop();
    delay(2000);
   }
   else {
    dropServo();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("  Moving Foward  ");
    moveShortDistances(200);
    delay(300);
   }
}
else {
  dropServo();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  Moving Foward  ");
  moveShortDistances(200);
  delay(300);
  }
}
