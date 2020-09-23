#include <DMXSerial.h>
#include <Wire.h>

#define NUM_LEDS 5

uint8_t ledTable[15];
void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.maxChannel(NUM_LEDS*3);
  Wire.begin(8);
  Wire.onRequest(requestEvent);

}

void requestEvent(){
  Wire.write(ledTable, 15);
  
}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 5000){
    if (DMXSerial.dataUpdated()){
      for (int i = 0; i < NUM_LEDS*3; i++){
        ledTable[i] = DMXSerial.read(i+1);
      }
    }
  }else{
    for (int i = 0; i < NUM_LEDS*3; i++){
      if(i%3 == 0){
        ledTable[i] = 255;
      }else{
        ledTable[i] = 0;
      }
    }
  }

}
