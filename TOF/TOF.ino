//Lib for using and Conecting to Aidafruit IO
#include <AdafruitIO.h>
#include <AdafruitIO_Dashboard.h>
#include <AdafruitIO_Data.h>
#include <AdafruitIO_Definitions.h>
#include <AdafruitIO_Feed.h>
#include <AdafruitIO_Group.h>
#include <AdafruitIO_MQTT.h>
#include <AdafruitIO_Time.h>
#include <AdafruitIO_WiFi.h>
#include "config.h"

// Lib for using I2C
#include <Wire.h>

// Lib for using the time of flight sensor
#include <Adafruit_VL6180X.h>

//TOF object
Adafruit_VL6180X tof = Adafruit_VL6180X();

void setup() {
  int conCount=0;
  startPixels();
  print("Connceting to Adafruit IO");
  io.connect();
  while(io.status()<AIO_CONNECTED && conCount<30){
    showPixels(0,0,0,255);
    print(".");
    conCount++;
    delay(500);
    showPixels(0,0,0,255);   
  }
  if(conCount==30)
  {
    showPixels(0,255,0,0);
  }
  if(!tof.begin())
  {
    tofNotFound();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  print("I´m Working dammit");
  if(!tof.begin())
  {
    tofNotFound();
  }
}


void tofNotFound()
{
  uint8_t i=0;;
    println("Tof sensor not found!!");
    while (!tof.begin())
    {
      showPixels(1,0,0,0);
      delay(1000);
      showPixels(1,255,0,0);
      i++;
      delay(1000);
      if(i>=3)
      {
        showPixels(1,0,0,0);
        delay(5000);
        i=0; 
      }    
    }
    return;
}
