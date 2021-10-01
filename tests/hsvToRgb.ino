int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int hPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int hValue = analogRead(hPin);

  // HSV to RGB
  double h = map(hValue, 0, 1023, 0, 359);
  double s = 1.0;
  double v = 1.0;
  int r, g, b;
  
  hsvToRgb2(h, s, v, &r, &g, &b);
  analogWrite(redPin, 255 - r);
  analogWrite(greenPin, 255 - g);
  analogWrite(bluePin, 255 - b);
  delay(50);
}

void hsvToRgb2(double h, double s, double v, int* r, int* g, int* b) {
  if (s == 0) {
    *r = 255;
    *g = 255;
    *b = 255;
    return;
  }
  
  double c = v * s;
  double hp = h / 60.0;
  double x = c * (1 - abs(modulo(hp, 2) - 1));
  
  double rp, gp, bp;
  if (hp <= 1){
    rp = c;
    gp = x;
    bp = 0;
  }
  else if (hp <= 2){
    rp = x;
    gp = c;
    bp = 0;
  }
  else if (hp <= 3){
    rp = 0;
    gp = c;
    bp = x;
  }
  else if (hp <= 4){
    rp = 0;
    gp = x;
    bp = c;
  }
  else if (hp <= 5){
    rp = x;
    gp = 0;
    bp = c;
  }
  else if (hp <= 6){
    rp = c;
    gp = 0;
    bp = x;
  }

  double m = v - c;
  *r = round(255 * (rp + m));
  *g = round(255 * (gp + m));
  *b = round(255 * (bp + m));

  return;
}

double modulo(double n, double mod) {
  if (n < mod) return n;
  else return modulo(n-mod, mod);
}
