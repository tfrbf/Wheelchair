#include <string.h>

int enA = 10;
int in1 = 9;
int in2 = 8;
int enB = 11;
int in3 = 13;
int in4 = 12;
char serial_data;
bool emr_stop = true;
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.print("Connected  to e-two\n");

}





//////////////////////////////////////////////////////
void loop() {
if (Serial.available()) {
  serial_data = Serial.read();
  Serial.println(serial_data);
  }
  
  if (serial_data == '1')
  demoone();
  
  if (serial_data == '2')
  {
    emr_stop = false;
    stop();
    emr_stop = true; 
  }

      
    
}


void demoone() {
  //Activate motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //analogWrite(enA, 200);  //set speed to 200

  //Activate motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //analogWrite(enB, 200);  //set speed to 200



for (int i = 0; i < 255; i++) {

    if (emr_stop == true){
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(30);
    }
    
  }

  // delay(2000);
  // // تغییر مسیر موتورها
  // digitalWrite(in1, LOW);   // غیر فعال شدن خروجی IN1
  // digitalWrite(in2, HIGH);  // فعال شدن خروجی IN2
  // digitalWrite(in3, LOW);   // غیر فعال شدن خروجی IN3
  // digitalWrite(in4, HIGH);  // فعال شدن خروجی IN4
  // delay(2000);              // تاخیر ۲ ثانیه
  // // خاموش شدن هر دو موتور
  // digitalWrite(in1, LOW);  // غیر فعال شدن
  // digitalWrite(in2, LOW);  // غیر فعال شدن
  // digitalWrite(in3, LOW);  // غیر فعال شدن
  // digitalWrite(in4, LOW);  // غیر فعال شدن
}


void forward() {
  // روشن شدن موتورها
  digitalWrite(in1, LOW);   // غیر فعال شدن خروجی IN1
  digitalWrite(in2, HIGH);  // فعال شدن خروجی IN2
  digitalWrite(in3, LOW);   // غیر فعال شدن خروجی IN3
  digitalWrite(in4, HIGH);  // فعال شدن خروجی IN4
  // تعیین شتاب از ۰ تا ماکزیمم سرعت
  for (int i = 0; i < 255; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
}


void stop() {
  digitalWrite(in1, LOW);  // غیر فعال شدن
  digitalWrite(in2, LOW);  // غیر فعال شدن

  digitalWrite(in3, LOW);  // غیر فعال شدن
  digitalWrite(in4, LOW);  // غیر فعال شدن

  // از ماکزیمم سرعت تا صفر
  for (int i = 255; i >= 0; i--) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
}
