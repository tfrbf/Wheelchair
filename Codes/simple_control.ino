int ENA = 10;  // to EnA of L298
int ENB = 11;
int IN1 = 9;  // to IN1 of L298
int IN2 = 8;  // to IN2 of L298
int IN3 = 13;
int IN4 = 12;
int serialdata = 0;
int data = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    Serial.print("Serial is Available\n");
    serialdata = Serial.read();
    Serial.println(serialdata);
  }

  if (serialdata == 'on')
    CW();

  if (serialdata == 'off')
    STOP();
}

void CW() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void CCW() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void STOP() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}d
