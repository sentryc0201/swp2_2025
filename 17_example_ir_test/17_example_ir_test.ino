// Arduino pin assignment

#define PIN_IR    0         // IR sensor at Pin A0
#define PIN_LED 9

#define _DIST_MIN 10
#define _DIST_MAX 25

#define _DUTY_MIN 540 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1450 // servo neutral position (90 degree)
#define _DUTY_MAX 2360 // servo full counterclockwise position (180 degree)

#define _EMA_ALPHA 0.5
#define INTERVAL 25

Servo myservo;

float dist_ema, dist_filtered, dist_raw
float dist_prev = _DIST_MIN;
long duty;
unsigned long last_sampling_time;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(200000);
  myservo.attach(PIN_SERVO);
}

void loop()
{
  if (millis() < last_sampling_time + INTERVAL)
    return;
    
  int a_value = analogRead(PIN_IR);

  dist_raw = (6762.0/(a_value - 9) - 4.0) * 10.0 - 60.0;
  if(dist_raw < _DIST_MIN || _DIST_MAX < dist_raw){
    dist_filtered = dist_prev;
    digitalWrite(PIN_LED, HIGH);
  } else{
    dist_prev = dist_raw;
    dist_filtered = dist_raw;
    digitalWrite(PIN_LED, LOW);
  }
  
  dist_ema = _EMA_ALPHA * dist_filtered + (1-_EMA_ALPHA) * dist_ema;

  duty = (long)(dist_ema - 10.0) * ((_DUTY_MAX - _DUTY_MIN)/(_DIST_MAX - _DIST_MIN)) + _DUTY_MIN;
  myservo.writeMicroseconds(duty);
  
  last_sampling_time += INTERVAL;

  Serial.print("_DUTY_MIN:");    Serial.print(_DUTY_MIN);
  Serial.print("_DIST_MIN:");  Serial.print(_DIST_MIN);
  Serial.print(",IR:");  Serial.print(a_value);
  Serial.print(",dist_raw:");  Serial.print(dist_raw);
  Serial.print(",ema:");   Serial.print(dist_ema);
  Serial.print(",servo:"); Serial.print(duty);  
  Serial.print(",_DIST_MAX:");   Serial.print(_DIST_MAX);
  Serial.print(",_DUTY_MAX:");  Serial.print(_DUTY_MAX);
  Serial.println("");
}
