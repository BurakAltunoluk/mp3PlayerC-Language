#include <IRremote.hpp>
#include <IRremote.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

IRrecv irrevc(9);
decode_results results;

static const uint8_t PIN_MP3_TX = 2; 
static const uint8_t PIN_MP3_RX = 3; 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

const int wirePin = 4; 
const int endPin = 5; 

DFRobotDFPlayerMini player;

int volume = 1;
int songNumber = 1;
boolean isPlaying = false;




void setup() {
  
Serial.begin(9600);

pinMode(wirePin, INPUT);
pinMode(endPin, INPUT);

 irrevc.enableIRIn();
 softwareSerial.begin(9600);

 if (player.begin(softwareSerial)) {
   Serial.println("OK");
    player.volume(volume);
    
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}


void loop() {
   
//   Serial.println(sensorValue);

  if (irrevc.decode(&results) ) {
   Serial.println(results.value);
   
    if (results.value == 33738799) {
    volume += 1;
    player.volume(volume);
       } 
       
    else  if (results.value == 33714319) {
        if (volume > 0) {
          volume -= 1;
          player.volume(volume);
          } 
    }
    
    else  if (results.value == 33730639 && isPlaying==false) {
     isPlaying = true ;  
     player.volume(volume);
     player.play();
       } 
       
       else  if (results.value == 33730639 && isPlaying==true) {
    player.stop();
    isPlaying = false;
       } 
       
       else  if (results.value == 33720439) { 
        songNumber += 1;
       player.stop();
       } 
       
       else  if (results.value == 33687799) {
       if (songNumber > 0) {
         songNumber -= 1;
       player.play(songNumber);
        }
       }
       
       else  if (results.value == 33731149) {
       player.stop();
       }
       
    irrevc.resume();
    }
    
   }
