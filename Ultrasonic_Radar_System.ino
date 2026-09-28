/*
  Arduino Ultrasonic Radar
  - Sweeps an HC-SR04 on a servo from 0 to 180 degrees and back
  - Sends "angle,distance." over Serial (9600 baud) for the HTML radar page

  Wiring:
    Servo    signal -> D9
    HC-SR04  TRIG   -> D10
    HC-SR04  ECHO   -> D11   (use a voltage divider: ECHO is 5V, better to step down to ~3.3V if your board needs it)
    Servo    +5V / GND -> external 5V supply recommended (servo can draw more current than the board's 5V pin)
*/

#include <Servo.h>

const int SERVO_PIN = 9;
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;

const int MAX_DISTANCE_CM = 100;   // ignore/clip anything farther than this
const int STEP_DEGREES = 2;        // servo step size per reading
const int STEP_DELAY_MS = 40;      // pause after each servo move, let it settle

Servo radarServo;
int angle = 0;
int direction = 1; // 1 = sweeping forward, -1 = sweeping back

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  radarServo.attach(SERVO_PIN);
  radarServo.write(angle);
  delay(500);
}

void loop() {
  radarServo.write(angle);
  delay(STEP_DELAY_MS);

  long distance = readDistanceCM();

  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");   // '.' terminates each reading, matches the HTML parser

  angle += direction * STEP_DEGREES;
  if (angle >= 180) {
    angle = 180;
    direction = -1;
  } else if (angle <= 0) {
    angle = 0;
    direction = 1;
  }
}

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 30ms timeout ~ avoids blocking forever if no echo returns
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    return MAX_DISTANCE_CM; // no echo = treat as "nothing in range"
  }

  long distance = duration * 0.0343 / 2; // speed of sound = 343 m/s
  if (distance > MAX_DISTANCE_CM) distance = MAX_DISTANCE_CM;
  return distance;
}
