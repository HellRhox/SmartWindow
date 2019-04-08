
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

#define radarPin 12
#define closed 5
#define buzzer 15


unsigned int activeTime = 6000;
unsigned int lastTime = 0;
unsigned int windowRange =0;

AdafruitIO_Feed *baseTime = io.feed("basetime");
AdafruitIO_Feed *range = io.feed("range");
  
void setup()
{
  
  startPixels();
  connectAIO();
  pinMode(radarPin, OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(radarPin, LOW);
  pinMode(radarPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(radarPin), handleInterrupt, RISING);
  io.run();
  baseTime->onMessage(getTimeInMs);
  range->onMessage(getRange);
  baseTime->get();
  lastTime= millis();
}

void loop() {
  io.run();
  range->get();
  if ((windowRange >= closed+3))
  {
    if (millis() >= (lastTime + activeTime))
    {
      doSomething(-1);
    }
  }
  delay(10000);
}

void getTimeInMs(AdafruitIO_Data *data)
{
  String t = (data->value());
  print("date->Value(): ");
  activeTime = t.toInt() * 60 * 100;
}


void getRange(AdafruitIO_Data *data)
{
  String t = (data->value());
  print("date->Value(): ");
  windowRange = t.toInt();
}



void handleInterrupt()
{
  lastTime = millis();
}

void doSomething(int i)
{
  switch (i)
  {
    // case -1 is justed used for debuging purposes and should not be used in a normal case
    case -1: 
             buzzing();
             println("___Debuge übersicht___");
             println("\n \n IOConnection Status:");print(io.statusText());
             println("\n \n activeTime:");print(activeTime);
             println("\n \n LastTime:");print(lastTime);
            // exit(0);
            break;
    case 0: showPixels(1, 255, 0, 255);
            break;
    case 1: buzzing();
            break;
    default: println("I don´t know what to do");
      break;
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

void buzzing()
{
  for(int i=0; i<3;i++)
  {
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
  }
}
