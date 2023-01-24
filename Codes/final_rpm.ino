#define _60secInMicrisec 60000000.0f
#define GearRatio 34.0f
#define EncoderCPR 360
#define pi 3.1415f


int ENA=10;  // to EnA of L298
int IN1=9;   // to IN1 of L298
int IN2=8;   // to IN2 of L298
int ENB=11;  // to EnA of L298
int IN3=13;   // to IN1 of L298
int IN4=12;   // to IN2 of L298



const byte ChA = 2; // to ENA (OutA / ChA) of Encoder
const byte ChB = 3; // to ENB (OutA / ChA) of Encoder

const byte ChA_2 = 4; // to ENA (OutA / ChA) of Encoder
const byte ChB_2 = 5; // to ENB (OutA / ChA) of Encoder

volatile unsigned long _1RevDuration; // Duration of 1 Revolution
volatile unsigned long _1RevDuration_2;


float rpm=0; // Motor Speed
float rpm_2=0;
volatile int feedbackDirection; // Direction Detected by Encoder
volatile int feedbackDirection_2;



enum desiredDirection{ // Desired Direction
  CW = 0, // Clockwise
  CCW = 1 // Counter Clockwise
};



float pwm; // PWM to L298
float pwm_2;

long counter =0; // Counter for Sinusoidal PWM Generation
long counter_2 =0;

void setPWM(float outputPWM); // Apply PWM to motor (input between 0-100)
void setPWM_2(float outputPWM_2);


void setDirection(desiredDirection dir); // Select Direction of Rotation
void setDirection_2(desiredDirection dir_2);

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  setDirection(CW); // set Initial Diretion to Clockwise
  setPWM(90); // initialize Motor
  setPWM_2(90);
  attachInterrupt(digitalPinToInterrupt(ChA), checkDirection, RISING); // Define Pin ChA as Intrrupt Pin
  attachInterrupt(digitalPinToInterrupt(ChA_2), checkDirection, RISING);
}

void loop() {
  pwm = 80.0f*sin(2.0f*pi*counter/100.0f);
  pwm_2 = 80.0f*sin(2.0f*pi*counter/100.0f);
  counter += 1;
  counter_2 += 1;
  // if (pwm > 0)
  //   setDirection(CW);
  // else
  //   setDirection(CCW);
  // setPWM(fabs(pwm));

  // if (pwm_2 > 0)
  //   setDirection(CW);
  // else
  //   setDirection(CCW);
  // setPWM(fabs(pwm_2));

  
  //delay(100);
  _1RevDuration =  pulseIn(ChA, LOW,10000)*EncoderCPR*2; // Calculating the Duration of a Revolution in micro seconds
  if (_1RevDuration == 0) // Avoiding from Singularity Problem
    rpm = 0;
  else
    rpm = feedbackDirection*_60secInMicrisec/((float)_1RevDuration*GearRatio); // Calculating Motor RPM
  Serial.print("Right Motor RPM: ") ;
  Serial.print(rpm);
  Serial.print("   \n");
  //Serial.println(pwm);

   _1RevDuration_2 =  pulseIn(ChA_2, LOW,10000)*EncoderCPR*2; // Calculating the Duration of a Revolution in micro seconds
  if (_1RevDuration_2 == 0) // Avoiding from Singularity Problem
    rpm_2 = 0;
  else
    rpm_2 = feedbackDirection_2*_60secInMicrisec/((float)_1RevDuration_2*GearRatio); // Calculating Motor RPM
  Serial.print("Left Motor RPM: ") ;   
  Serial.print(rpm_2);
  Serial.print("   ");
  //Serial.println(pwm_2);
}

void setDirection(desiredDirection dir){
  switch(dir){
    case CW:
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      break;
    case CCW:
      digitalWrite(IN2,LOW);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(IN3,HIGH);
      break;
  }
}



void setPWM(float outputPWM){
  analogWrite(ENA,outputPWM*255/100);
  
}



void setPWM_2(float outputPWM_2){
  analogWrite(ENB,outputPWM_2*255/100);
  
}


void checkDirection(){
  feedbackDirection = 2*bitRead(PIND,ChB)+1;
  feedbackDirection_2 = 2*bitRead(PIND,ChB)+1;
}