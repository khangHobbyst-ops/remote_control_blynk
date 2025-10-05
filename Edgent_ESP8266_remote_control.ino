/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

#define BLYNK_TEMPLATE_ID "TMPL6fPxhU0cE"
#define BLYNK_TEMPLATE_NAME "LED"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

const int buttonPin = D2;  // the number of the pushbutton pin
const int relayPin = D7;    // the number of the LED pin

// variables will change:
bool buttonState = 0;  // variable for reading the pushbutton status

unsigned long previousMillis = 0;
const long interval = 250; 

BlynkTimer timer;
int ETA_min;


void setup()
{
  digitalWrite(relayPin, HIGH);
  // initialize the LED pin as an output:
  pinMode(relayPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);

  BlynkEdgent.begin();
}

void switchButton(){
  buttonState=!buttonState;
  if (buttonState){
    Blynk.logEvent("running");
  }
      
}
BLYNK_WRITE(V0){
  switchButton();
}

BLYNK_WRITE(V1){
  ETA_min = param.asInt();
}
BLYNK_WRITE(V2){
  enable_timer = param.asInt();
}
void loop() {
  BlynkEdgent.run();

  unsigned long currentMillis = millis();
  
  if ( digitalRead(buttonPin) == LOW)
  {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Save the last time the LED toggled
      switchButton();
      Blynk.virtualWrite(V0, buttonState);
    }
    
  }

  //handle output acroding to buttonState
  if (buttonState) {
        // turn relay on
    digitalWrite(relayPin, LOW);


  } else {
        // turn relay off
    digitalWrite(relayPin, HIGH);
  }

}

