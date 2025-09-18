# define LED_PIN 9
# define PERIOD 10000

int setp; // 0 ~ 200
int setp_period; // period for one setp
int setp_dir;

int set_period(int period){ // cal period for one setp
  return period / 200;
}

int set_duty(int setp_period, int setp){ // cal duty for %
  return setp;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  setp = 0;
  setp_dir = 1;
  setp_period = set_period(PERIOD);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int hightime, lowtime, duty; // if High, turn on led

  duty = set_duty(setp_period, setp);
  hightime = (setp_period * duty) / 100;
  lowtime = setp_period - hightime;

  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(hightime);
  digitalWrite(LED_PIN, LOW);
  delayMicroseconds(lowtime);

  Serial.println(hightime);
    
  if (setp == 100) setp_dir = -1;
  if (setp == 0) setp_dir = 1;

  setp += setp_dir;
}
