#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2,13,NEO_RGBW+NEO_KHZ800);


void startPixels() //Initialisiert die Pixel und startet sie im zustand "off"
{
  pixels.begin();
  pixels.show();
};


void showPixels(uint8_t numberOfPixel, uint8_t red, uint8_t green, uint8_t blue) //uint8_t ist eine kurzschreibform für einen Integer ohne vorzeichen der 8 bit also ein byte lang ist.
{
  pixels.setPixelColor(numberOfPixel,green,red,blue);
  pixels.show();
};
