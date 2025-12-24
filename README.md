# Animatronic Snowman

Four-servo animatronic snowman routine. Demo video: https://youtube.com/shorts/crhkF1Pt4T4?si=v03Tk1DF2dJ6dqVK

## Hardware (direct pins)
- Arduino-compatible board (e.g., Uno)
- 4x hobby servos (left arm, right arm, head tilt, torso twist)
- External 5V supply for the servos, shared ground with the Arduino
- Jumper wires
  - Pins: left arm 3, right arm 5, head 6, torso 9.

## Using a PCA9685 servo driver (I2C)
- Install the Arduino Library Manager package: “Adafruit PWM Servo Driver Library”.
- Wiring (Uno/Nano):
  - PCA9685 VCC → Arduino 5V
  - PCA9685 GND → Arduino GND
  - SDA → A4
  - SCL → A5
- Servo power (important):
  - External 5V supply (2A+; 3–5A if the arms are heavy)
  - Supply + → PCA9685 V+ terminal (servo power)
  - Supply – → PCA9685 GND (same rail as above)
  - Common ground required: Arduino GND and PCA9685 GND are tied via the GND wire above.
- Channel assignment:
  - Channel 0 = Left arm
  - Channel 1 = Right arm
  - Channel 2 = Head
  - Channel 3 = Torso
- Servo wire order on the PCA9685 ports: Brown/Black = GND, Red = V+, Orange/Yellow = Signal.

## What the sketch does
- Starts from a neutral 90° pose, then performs arm/head/torso swings in timed clusters.
- Uses `pose(...)` for quick position changes and `moveSmooth(...)` for slow sweeps.
- Returns to neutral between sequences to reduce drift.

## Tuning
- Reduce strain: bump delays slightly higher or trim angle extremes.
- Change the choreography: edit the angle sets inside the `loop()` sequences.
- Invert a servo direction: swap its angle endpoints (e.g., `30` ↔ `150`).

## Repo layout
- `AnimatronicSnowman.ino` — Arduino sketch for direct-to-pin servos.
- `AnimatronicSnowman_PCA9685.ino` — Arduino sketch for PCA9685 I2C servo driver (Adafruit library).
