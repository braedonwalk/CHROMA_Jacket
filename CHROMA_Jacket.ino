#include <Adafruit_NeoPixel.h>
int numLed = 100;
int stripPin = 12;
Adafruit_NeoPixel strip(numLed, stripPin, NEO_GRB + NEO_KHZ800);

#include <Bounce2.h>

Bounce but1 = Bounce();
Bounce but2 = Bounce();

const int but1Pin = 2;  // the number of the pushbutton pin
const int but2Pin = 3;  // the number of the pushbutton pin
//const int but1Pin = 33;  // the number of the pushbutton pin

void setup() {
  but1.attach(but1Pin, INPUT);
  but2.attach(but2Pin, INPUT);
  but1.interval(50);
  but2.interval(50);

  strip.begin();
  strip.setBrightness(50);
  strip.clear();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  but1.update();
  but2.update();

  if (but1.rose()) {
    Serial.println("1");
    rainbow();
  }

  if (but2.rose()) {
    strip.clear();
    Serial.println("2");
  }

  strip.show();
}

void rainbow() {
  strip.clear();
  static int rainbowCycles = 0;
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i + rainbowCycles) & 255));
  }
  strip.show();
  rainbowCycles++;
  if (rainbowCycles >= 256) rainbowCycles = 0;
}
