#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 12;
const int IN4 = 11;
const int ENB = 6;
#define TRIG_PIN 4
#define ECHO_PIN 5
#define BUZZER_PIN 10
const int switchPin = 2;
const int THRESHOLD_DISTANCE = 30;
bool motorRunning = false;
int speedValue = 255;

void setup() {
Serial.begin(9600);
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(switchPin, INPUT_PULLUP);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(BUZZER_PIN, OUTPUT);
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("System Ready...");
delay(2000);
lcd.clear();
stopMotor();
}
void loop() {
int distance = getDistance();
sendToMATLAB(distance);
if (digitalRead(switchPin) == LOW) {
if (!motorRunning && distance > 10) {
startMotor(speedValue);
}
handleBuzzer(distance);
} else {
if (motorRunning && distance > THRESHOLD_DISTANCE) {
stopMotor();
}

adjustSpeed(distance);
}
updateLCD(distance);
delay(200);
}
void startMotor(int pwm) {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(ENA, pwm);
analogWrite(ENB, pwm);
motorRunning = true;
}
void stopMotor() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
analogWrite(ENA, 0);
analogWrite(ENB, 0);
motorRunning = false;
}
int getDistance() {
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

long duration = pulseIn(ECHO_PIN, HIGH, 30000);
return duration * 0.034 / 2;
}
void sendToMATLAB(int distance) {
Serial.println(distance);
}
void playCautionTone() {
tone(BUZZER_PIN, 1000);
delay(200);
noTone(BUZZER_PIN);
}
void playDangerTone() {
tone(BUZZER_PIN, 2000);
}
void handleBuzzer(int distance) {
if (distance > THRESHOLD_DISTANCE) {
noTone(BUZZER_PIN);
} else if (distance > 10 && distance <= THRESHOLD_DISTANCE) {
playCautionTone();
} else {
playDangerTone();
stopMotor();
}
}
void adjustSpeed(int distance) {
if (distance > THRESHOLD_DISTANCE) {
speedValue = 255;
noTone(BUZZER_PIN);
if (motorRunning) {

analogWrite(ENA, speedValue);
analogWrite(ENB, speedValue);
}
} else if (distance > 10) {
speedValue = 150;
playCautionTone();
if (motorRunning) {
analogWrite(ENA, speedValue);
analogWrite(ENB, speedValue);
}
} else {
speedValue = 0;
playDangerTone();
stopMotor();
}
}
void updateLCD(int distance) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Distance: ");
lcd.print(distance);
lcd.print("cm");
lcd.setCursor(0, 1);
if (distance > THRESHOLD_DISTANCE) {
lcd.print("Status: SAFE ");
} else if (distance > 10) {
lcd.print("Status: CAUTION");
} else {
lcd.print("!!! DANGER !!! ");}}