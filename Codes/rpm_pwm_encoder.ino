#define _60secInMicrisec 60000000.0f
#define GearRatio 34.0f
#define EncoderCPR 360
#define pi 3.1415f
int ENA=10;  // to EnA of L298
int IN1=9;   // to IN1 of L298
int IN2=8;   // to IN2 of L298
const byte ChA = 2; // to ENA (OutA / ChA) of Encoder
const byte ChB = 3; // to ENB (OutA / ChA) of Encoder

volatile unsigned long _1RevDuration; // Duration of 1 Revolution
float rpm=0; // Motor Speed
volatile int feedbackDirection; // Direction Detected by Encoder
enum desiredDirection{ // Desired Direction
  CW = 0, // Clockwise
  CCW = 1 // Counter Clockwise
};

float pwm; // PWM to L298
long counter =0; // Counter for Sinusoidal PWM Generation

void setPWM(float outputPWM); // Apply PWM to motor (input between 0-100)
void setDirection(desiredDirection dir); // Select Direction of Rotation

void setup() {
  Serial.begin(1200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  setDirection(CW); // set Initial Diretion to Clockwise
  setPWM(90); // initialize Motor
  attachInterrupt(digitalPinToInterrupt(ChA), checkDirection, RISING); // Define Pin ChA as Intrrupt Pin
}

void loop() {
  pwm = 80.0f*sin(2.0f*pi*counter/100.0f);
  counter += 1;
  if (pwm > 0)
    setDirection(CW);
  else
    setDirection(CCW);
  setPWM(fabs(pwm));
  //delay(100);
  _1RevDuration =  pulseIn(ChA, LOW,10000)*EncoderCPR*2; // Calculating the Duration of a Revolution in micro seconds
  if (_1RevDuration == 0) // Avoiding from Singularity Problem
    rpm = 0;
  else
    rpm = feedbackDirection*_60secInMicrisec/((float)_1RevDuration*GearRatio); // Calculating Motor RPM
  Serial.print(rpm);
  Serial.print("   ");
  Serial.println(pwm);
}

void setDirection(desiredDirection dir){
  switch(dir){
    case CW:
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      break;
    case CCW:
      digitalWrite(IN2,LOW);
      digitalWrite(IN1,HIGH);
      break;
  }
}
void setPWM(float outputPWM){
  analogWrite(ENA,outputPWM*255/100);
}
void checkDirection(){
  feedbackDirection = -2*bitRead(PIND,ChB)+1;
}