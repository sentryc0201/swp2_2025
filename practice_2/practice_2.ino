#define PIN_LED 9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0
#define INTERVAL 100
#define PULSE_DURATION 10
#define _DIST_MIN 100.0
#define _DIST_MAX 300.0

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = USS_measure(PIN_TRIG, PIN_ECHO);

  if ((distance == 0.0) || (distance > _DIST_MAX)){
    distance = _DIST_MAX + 10.0;
    digitalWrite(PIN_LED, 1);
  } else if (distance < _DIST_MIN){
    distance = _DIST_MAX - 10.0;
    digitalWrite(PIN_LED, 1);
  } else {
    digitalWrite(PIN_LED, 0);
  }

  Serial.print("Min:"); Serial.print(_DIST_MIN);
  Serial.print(",distance:"); Serial.print(distance);
  Serial.print("Max:"); Serial.print(_DIST_MAX);
  Serial.println(""); 

  delay(50);

  delay(INTERVAL);
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}
