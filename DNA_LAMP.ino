#include <Stepper.h>


#define MOTOR_STEPS 2048

#define MOTOR_IN1 13
#define MOTOR_IN2 12
#define MOTOR_IN3 14
#define MOTOR_IN4 27
#define MODE_1 26
#define MODE_2 25
#define LED_CONTROL 2

const int ledPin = 16;
const int controlPin = 2;
const int buttonPin = 17;
const int freq = 5000;
const int resolution = 8;

int brightness = 0;
int fadeAmount = 5;

// initialize the stepper library
Stepper myStepper(MOTOR_STEPS, MOTOR_IN1, MOTOR_IN3, MOTOR_IN2, MOTOR_IN4);

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Communication established!");
  myStepper.setSpeed(5);
  pinMode(MODE_1, INPUT_PULLUP);
  pinMode(MODE_2, INPUT_PULLUP);
}

void loop() {
  int modeOne = digitalRead(MODE_1);
  int modeTwo = digitalRead(MODE_2);
  Serial.println("HELLO WORLD");

  if(modeOne == HIGH) {
    Serial.println("Mode 1: ON");
  }

  if(modeTwo == HIGH) {
    Serial.println("Mode 2: ON");
  }
}

void dimmLeds() {
    ledcWrite(ledPin, brightness);
    ledcWrite(controlPin, brightness);		

    brightness = brightness + fadeAmount;
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ; 
    }
}

void rotate() {
  Serial.println("rotate");
  myStepper.step(MOTOR_STEPS);
}
