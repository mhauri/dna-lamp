#include <Stepper.h>

// PINS
#define MOTOR_IN1 13
#define MOTOR_IN2 12
#define MOTOR_IN3 14
#define MOTOR_IN4 27
#define MODE_1 26
#define MODE_2 25
#define LED_PWM 15


// STEPPER MOTOR SETTINGS
#define MOTOR_STEPS 2048
#define MOTOR_SPEED 10
#define MOTOR_PERIOD 20

// LED'S
#define FADE_AMOUNT 5
#define LED_PERIOD 50
#define LED_PAUSE 8000

// INITIALIZE STEPPER LIBRARY
Stepper myStepper(MOTOR_STEPS, MOTOR_IN1, MOTOR_IN3, MOTOR_IN2, MOTOR_IN4);

// VARIABLES 
int brightness = 0;
int fadeAmount = FADE_AMOUNT;
unsigned long ledTime = 0;
const unsigned long ledPeriod = LED_PERIOD;
const unsigned long ledPause = LED_PAUSE;
unsigned long motorTime = 0;
const unsigned long motorPeriod = MOTOR_PERIOD;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Communication established!");
  myStepper.setSpeed(MOTOR_SPEED);
  pinMode(MODE_1, INPUT_PULLUP);
  pinMode(MODE_2, INPUT_PULLUP);
  pinMode(LED_PWM, OUTPUT);
}

void loop() {
  int modeOne = digitalRead(MODE_1);
  int modeTwo = digitalRead(MODE_2);

  if(modeOne == LOW) {
    dimmLeds();
  }
  if(modeTwo == LOW) {
    dimmLeds();
    rotate();
  }

  if(modeOne == HIGH && modeTwo == HIGH) {
    reset();
  }
}

void dimmLeds() {
    unsigned long current = millis();
    if(current - ledTime >= ledPeriod) {
      ledTime = current;
      brightness = brightness + fadeAmount;
      if (brightness == 0 || brightness == 255) {
        fadeAmount = -fadeAmount;
      }
      analogWrite(LED_PWM, brightness);
    }
}

void rotate() {
  unsigned long current = millis();
  if(current - motorTime >= motorPeriod) {
    motorTime = current;
    myStepper.step(1);
  }
}

void reset() {
  brightness = 5;
  analogWrite(LED_PWM, 0);
  digitalWrite(MOTOR_IN1, 0);
  digitalWrite(MOTOR_IN2, 0);
  digitalWrite(MOTOR_IN3, 0);
  digitalWrite(MOTOR_IN4, 0);
}
