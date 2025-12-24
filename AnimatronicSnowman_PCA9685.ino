#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Animatronic Snowman routine using a PCA9685 16-channel PWM/servo driver (I2C)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const uint8_t CH_LEFT  = 0;
const uint8_t CH_RIGHT = 1;
const uint8_t CH_HEAD  = 2;
const uint8_t CH_TORSO = 3;

// Pulse counts for ~0° and ~180° at 50 Hz (12-bit range 0-4095). Tweak if your servos differ.
const uint16_t PULSE_MIN = 110;  // ~500 us
const uint16_t PULSE_MAX = 520;  // ~2400 us

void writeServo(uint8_t channel, int angle) {
  angle = constrain(angle, 0, 180);
  uint16_t pulse = map(angle, 0, 180, PULSE_MIN, PULSE_MAX);
  pwm.setPWM(channel, 0, pulse);
}

void pose(int la, int ra, int h, int t) {
  writeServo(CH_LEFT, la);
  writeServo(CH_RIGHT, ra);
  writeServo(CH_HEAD, h);
  writeServo(CH_TORSO, t);
}

void moveSmooth(uint8_t channel, int fromA, int toA, int d) {
  if (toA > fromA) {
    for (int a = fromA; a <= toA; a++) { writeServo(channel, a); delay(d); }
  } else {
    for (int a = fromA; a >= toA; a--) { writeServo(channel, a); delay(d); }
  }
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);  // Standard analog servo rate
  delay(10);

  pose(90, 90, 90, 90);
  delay(800);
}

void loop() {
  for (int i = 0; i < 2; i++) {
    pose(60, 120, 80, 70); delay(220);
    pose(120, 60, 100, 110); delay(220);
    pose(75, 105, 70, 80); delay(180);
    pose(105, 75, 110, 100); delay(180);
  }

  for (int i = 0; i < 4; i++) {
    pose(40, 110, 70, 95); delay(160);
    pose(70, 140, 110, 85); delay(160);
  }

  for (int i = 0; i < 3; i++) {
    pose(60, 120, 120, 60); delay(220);
    pose(120, 60, 60, 120); delay(220);
  }

  moveSmooth(CH_TORSO, 90, 130, 8);
  moveSmooth(CH_HEAD, 90, 50, 8);
  moveSmooth(CH_LEFT, 90, 30, 6);
  moveSmooth(CH_RIGHT, 90, 150, 6);
  delay(250);

  moveSmooth(CH_TORSO, 130, 50, 8);
  moveSmooth(CH_HEAD, 50, 130, 8);
  moveSmooth(CH_LEFT, 30, 140, 6);
  moveSmooth(CH_RIGHT, 150, 40, 6);
  delay(300);

  pose(90, 90, 90, 90);
  delay(900);
}
