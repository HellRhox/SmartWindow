
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

//defining the pin that is used for shuting down the TOF sensor when not in use to save energy
#define shutdownPin 12



unsigned long last_feed;
unsigned int feed;
//Object that is used to define the feed you want you´re data to be pushed to
AdafruitIO_Feed *Range = io.feed("range");

void setup() {
  last_feed=0;
  pinMode(shutdownPin,OUTPUT);
  startPixels();
  connectAIO();
  if (!tof.begin())
  {
    tofNotFound();
  }
}

void loop() {
  io.run();
  if (millis()>=last_feed+57000)
  {
    digitalWrite(shutdownPin,HIGH);
    if (!tof.begin())
    {
      tofNotFound();
      println("Something went horribliy wrong");
    }
    else
    {
      
      if (tof.readRangeStatus()==VL6180X_ERROR_NONE)
      {
        int i=0;
        feed=0;
        while(millis()<=(last_feed+60000))
        {
          feed+=tof.readRange();
          i++;
        }
        feed/=i;
      }
      if (millis()>=(last_feed+60000))
      {
        print("sending-> ");println(feed);
        Range->save(feed);
        last_feed=millis();
        digitalWrite(shutdownPin,LOW);
      }
    }
  }
  else
  {
    digitalWrite(shutdownPin,LOW);
  }
    
}

// function for connectiong to Adafruit IO
void connectAIO()
{
  int conCount = 0;
  println("Connceting to Adafruit IO");
  io.connect();
  while (io.status() < AIO_CONNECTED && conCount < 60) {
    showPixels(0, 0, 0, 255);
    print(".");
    conCount++;
    delay(250);
    showPixels(0, 0, 0, 0);
    delay(250);
  }
  print("\n");
  println(io.statusText());

  if (io.status() == 21)
  {
    showPixels(0, 0, 255, 0);
  }
  else
  {
    showPixels(0, 255, 0, 0);
  }
}

//Function that should be called to handle a disconnect of the TOF sensor
void tofNotFound()
{
  uint8_t i = 0;;
  println("Tof sensor not found!!");
  while (!tof.begin())
  {
    showPixels(1, 0, 0, 0);
    delay(1000);
    showPixels(1, 255, 0, 0);
    i++;
    delay(1000);
    if (i >= 3)
    {
      showPixels(1, 0, 0, 0);
      delay(5000);
      i = 0;
    }
  }
  return;
}
