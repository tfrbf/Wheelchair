    /*
  HN3806-AB-Rotary-Encoder
  modified on 12 oct 2020
  by Amir Mohamad Shojaee @ Electropeak
  Home<iframe class="wp-embedded-content" sandbox="allow-scripts" security="restricted" style="position: absolute; clip: rect(1px, 1px, 1px, 1px);" title="&#8220;Home&#8221; &#8212; Electropeak" src="https://electropeak.com/learn/embed/#?secret=VaryXI9bX2" data-secret="VaryXI9bX2" width="600" height="338" frameborder="0" marginwidth="0" marginheight="0" scrolling="no"></iframe>

  Based on electricdiylab.com Example
*/

//This variable will increase or decrease depending on the rotation of encoder
volatile long x , counter = 0; 
    
void setup() {
  Serial.begin (9600);
  pinMode(2, INPUT_PULLUP); 
  
  pinMode(3, INPUT_PULLUP); 
   
  attachInterrupt(0, A, RISING);
   
  attachInterrupt(1, B, RISING);
  }
   
  void loop() {
  // Send the value of counter
  if( counter != x ){
  Serial.println (counter);
  x = counter;
  }
  }
   
  void A() {
  if(digitalRead(3)==LOW) {
  counter++;
  }else{
  counter--;
  }
  }
   
  void B() {
  if(digitalRead(2)==LOW) {
  counter--;
  }else{
  counter++;
  }
}
