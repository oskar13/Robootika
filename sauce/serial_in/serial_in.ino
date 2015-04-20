#include <HT1632.h>

int bars[32] = {1,2,3,4,5,6,7,8,7,6,5,4,3,2,1,1,2,3,4};

int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int val2= 1;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5); 
  HT1632.begin(9,10,11);
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT

}


void loop() {
  while(!Serial.available());
  int ct = Serial.parseInt();
 
 if (ct > 8) {
   ct = 8;
 } else if (ct < 0) {
   ct = 0;
 }
  
  HT1632.clear();
  // put your main code here, to run repeatedly:
  
  //HT1632.drawImage(IMG_SAILBOAT, IMG_SAILBOAT_WIDTH,  IMG_SAILBOAT_HEIGHT, 8, 0);
  //HT1632.setPixel(random(0, 32) ,random(0, 7) :);


  //bars[1] = bars[0];
  
  
  val = analogRead(potPin);    // read the value from the sensor
  //digitalWrite(ledPin, HIGH);  // turn the ledPin on
  //delay(val);                  // stop the program for some time
  //digitalWrite(ledPin, LOW);   // turn the ledPin off
  //delay(val);                  // stop the program for some time
  val2 = val / 64;
  if (val2 == 0) {
    val2 = 1;
  }
  
  HT1632.setBrightness(val2);
  
  for (int j = 31; j>=0 ;j--) {
    if (j>0){
      bars[j] = bars[j-1];
    } else {
      bars[j] = ct;
    }
    drawBar(bars[j], j);
    
  }
  
  //Serial.write(ct);
  
//bars[0]=random(0,9);


  HT1632.render();
  //delay(50);
  
}

void drawBar(int height,int posx) {
  if (height > 8) {
    height == 8;
  } else if (height<1) {
    return;
  }
  int leaveBlank=8-height;
  //HT1632.setPixel(posx, height);
  for (int i = 7; i >=leaveBlank; i--){
    HT1632.setPixel(posx, i);
  }
}
