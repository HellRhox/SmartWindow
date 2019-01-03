
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




void setup() {
}

void loop() {

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
