#include <FastLED.h>

#include <Wire.h>


#define NUM_LEDS 5
#define DATA_PIN 2

#define HUE_POT A2
#define SAT_POT A1
#define VAL_POT A3

#define MODE_SWITCH 6

CRGB LED[NUM_LEDS];

byte ledTable[15];
int hue = 255;
int sat = 255;
int val = 255;

void setup() {
  pinMode(HUE_POT,INPUT);
  pinMode(SAT_POT,INPUT);
  pinMode(VAL_POT,INPUT);
  pinMode(MODE_SWITCH,INPUT_PULLUP);
  Wire.begin();
  Serial.begin(9600);
  FastLED.addLeds<PL9823,DATA_PIN, RGB>(LED, NUM_LEDS);
}

void PRINT_ARRAY(){
  Serial.println("==================");
  Serial.print(ledTable[0]);
  Serial.print(',');
  Serial.print(ledTable[1]);
  Serial.print(',');
  Serial.print(ledTable[2]);
  Serial.println();
}



void loop() {
  Wire.requestFrom(8,NUM_LEDS*3);
  while (Wire.available()){
    for (int i = 0; i < NUM_LEDS*3; i++){
      ledTable[i] = Wire.read();
    }
  }
  hue = map((analogRead(HUE_POT)),0,1023,255,0);
  sat = map((analogRead(SAT_POT)),0,1023,255,0);
  val = map((analogRead(VAL_POT)),0,1023,0,255);
  //PRINT_ARRAY();
  //delay(250);
  //LED[0] = CRGB(ledTable[0],ledTable[1],ledTable[2]);
  //FastLED.show();
  int offset =  0;
  if (digitalRead(MODE_SWITCH) == HIGH){
    for (int i = 0; i < NUM_LEDS*3; i++){
      LED[i] = CRGB(ledTable[i+0+offset],ledTable[i+1+offset],ledTable[i+2+offset]);
      offset += 2;
    }
  }else{
      for (int i = 0; i < NUM_LEDS*3; i++){
        LED[i] = CHSV(hue,sat,val);
      }
    }
  FastLED.show();
  
}
