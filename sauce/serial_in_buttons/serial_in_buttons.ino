#include <HT1632.h>

int bars[32] = {1,2,3,4,5,6,7,8,7,6,5,4,3,2,1,1,2,3,4};

int potPin = 2;    // select the input pin for the potentiometer
int motPin = 4;

int lightSensePin = 1;  
int lightVal = 0; // 0 to 850

int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int val2= 1;

int delaycount = 0;

bool dontskip = true;

float scale = 3.5;

const int buttonPin = 2;     // the number of the pushbutton pin
const int buttonPin2 = 7;     // the number of the pushbutton pin2


int buttonState = 0;
int buttonState2 = 0;

bool useLightSensor = false;


int sensor_1 = HIGH;
int cooldown = 0;


void setup() {
    Serial.begin(9600);
    Serial.setTimeout(5); 
    HT1632.begin(9,10,11);
    pinMode(buttonPin, INPUT);
    pinMode (motPin,INPUT);

}


void loop() {
    while(!Serial.available());

    lightVal = analogRead(lightSensePin);



    delaycount +=1;

    if (delaycount == 10) {
        dontskip = false;
        sensor_1 = digitalRead(motPin);
        delaycount = 0;
    }

    if ( sensor_1 == LOW) {
        cooldown -= 1;
    } else {
        cooldown = 1000;
    }



    int ct = Serial.parseInt();
    ct = ct / scale;
    

    if (sensor_1 == HIGH || cooldown > 0 || true){











//if (ct > 8) {
//  ct = 8;
//} else if (ct < 0) {
//  ct = 0;
//}

        HT1632.clear();
// put your main code here, to run repeatedly:

//HT1632.drawImage(IMG_SAILBOAT, IMG_SAILBOAT_WIDTH,  IMG_SAILBOAT_HEIGHT, 8, 0);
//HT1632.setPixel(random(0, 32) ,random(0, 7) :);


//bars[1] = bars[0];


        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {    
// turn LED on:    
            scale = scale + 0.2f;
            if (scale > 8.f) {
                scale = 1.f;
            } 
        } 



        buttonState2 = digitalRead(buttonPin2);

        if (buttonState2 == HIGH) {    
          useLightSensor = !useLightSensor;
      } 







val = analogRead(potPin);    // read the value from the sensor
//digitalWrite(ledPin, HIGH);  // turn the ledPin on
//delay(val);                  // stop the program for some time
//digitalWrite(ledPin, LOW);   // turn the ledPin off
//delay(val);                  // stop the program for some time

if (useLightSensor) {
  val2 = lightVal / 53;

} else {
  val2 = val / 64;

}

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

} else {

    HT1632.setBrightness(1);

    //HT1632.clear();
    //HT1632.render();
    dontskip = true;
}

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
