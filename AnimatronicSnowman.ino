#include <Servo.h>

// Animatronic Snowman routine — four servos: left/right arms, head tilt, torso twist
Servo leftArm, rightArm, head, torso;

const int PIN_LEFT  = 3;
const int PIN_RIGHT = 5;
const int PIN_HEAD  = 6;
const int PIN_TORSO = 9;

void pose(int la, int ra, int h, int t) {
  leftArm.write(la);
  rightArm.write(ra);
  head.write(h);
  torso.write(t);
}

void moveSmooth(Servo &s, int fromA, int toA, int d) {
  if (toA > fromA) for (int a = fromA; a <= toA; a++) { s.write(a); delay(d); }
  else for (int a = fromA; a >= toA; a--) { s.write(a); delay(d); }
}

void setup() {
  leftArm.attach(PIN_LEFT);
  rightArm.attach(PIN_RIGHT);
  head.attach(PIN_HEAD);
  torso.attach(PIN_TORSO);

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

  moveSmooth(torso, 90, 130, 8);
  moveSmooth(head, 90, 50, 8);
  moveSmooth(leftArm, 90, 30, 6);
  moveSmooth(rightArm, 90, 150, 6);
  delay(250);

  moveSmooth(torso, 130, 50, 8);
  moveSmooth(head, 50, 130, 8);
  moveSmooth(leftArm, 30, 140, 6);
  moveSmooth(rightArm, 150, 40, 6);
  delay(300);

  pose(90, 90, 90, 90);
  delay(900);
}
