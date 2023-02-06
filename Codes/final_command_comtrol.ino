
int enA = 10;
int in1 = 9;
int in2 = 8;
int enB = 11;
int in3 = 13;
int in4 = 12;
String serial_data;
bool emr_stop = true;

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  if (Serial.available());
  Serial.print("Connected  to e-two\n");
}

void loop() {
  if (Serial.available()) {
    serial_data = Serial.readString();
    Serial.println(serial_data);
  }

  if (serial_data == 'on') {
    forward();
    Serial.println("Going Forward");
  }



  if (serial_data == 'off') {
    emr_stop = false;
    stop();
    emr_stop = true;
    Serial.println("Stopping!");
  }
}

void forward() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  for (int i = 0; i < 255; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
  }
}


void stop() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  for (int i = 255; i >= 0; i--) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
}
