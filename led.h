/* #define FASTLED_RGBW
  #include <FastLED.h>

  #define NUM_STRIPS 1
  #define NUM_LEDS 20
  #define BRIGHTNESS 5
  #define LED_TYPE SK6812
  #define COLOR_ORDER GRB
  #define FASTLED_ALLOW_INTERRUPTS 0
  #define FASTLED_INTERRUPT_RETRY_COUNT 1
  #define FRAMES_PER_SECOND 60
  #define COOLING 55
  #define SPARKING 120

  bool gReverseDirection  = false;

  const int stripPin   = 2;
  #define FASTLED_RGBW
  #include <FastLED.h>

  #define NUM_STRIPS 1
  #define NUM_LEDS 20
  #define BRIGHTNESS 5
  #define LED_TYPE SK6812
  #define COLOR_ORDER GRB
  #define FASTLED_ALLOW_INTERRUPTS 0
  #define FASTLED_INTERRUPT_RETRY_COUNT 1
  #define FRAMES_PER_SECOND 60
  #define COOLING 55
  #define SPARKING 120

  bool gReverseDirection = false;

  const int stripPin = 2;

  CRGB leds[NUM_LEDS];
  CRGBPalette16 gPal;

  unsigned long lastUpdate = 0; // will store last time LED was updated
  const long interval = 150;    // interval at which to update LED (milliseconds)

  void updateLedWithNonBlockingDelay(void (*colorSetter)(int), bool forward) {
  static int currentLed = forward ? 0 : NUM_LEDS - 1;
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdate >= interval) {
    lastUpdate = currentMillis;

    // Call the function pointer to set the color
    colorSetter(currentLed);

    FastLED.show();

    // Reset the LED to off after showing
    leds[currentLed] = CRGB::Black;

    // Move to the next LED
    if (forward) {
      currentLed++;
      if (currentLed >= NUM_LEDS) currentLed = 0;
    } else {
      currentLed--;
      if (currentLed < 0) currentLed = NUM_LEDS - 1;
    }
  }
  }

  void setGreen(int ledIndex) {
  leds[ledIndex] = CRGB(0, 128, 0);
  }

  void setYellow(int ledIndex) {
  leds[ledIndex] = CRGB::Goldenrod;
  }

  void setOrange(int ledIndex) {
  leds[ledIndex] = CRGB(255, 140, 0);
  }

  void setRed(int ledIndex) {
  leds[ledIndex] = CRGB(178, 34, 34);
  }
  CRGB leds[NUM_LEDS];
  CRGBPalette16 gPal;

  void greenLed()
  {
  for (int dot = (NUM_LEDS - 1) ; dot >= 0 ; dot--)
  {
    leds[dot].setRGB(0, 128, 0);
    FastLED.show();
    delay(150);
  }

  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    leds[dot].setRGB(0, 0, 0);
    FastLED.show();
    delay(150);
  }
  }

  void yellowLed() {
  for (int dot = (NUM_LEDS - 1) ; dot >= 0 ; dot--)
  {
    leds[dot] = CRGB::Goldenrod;
    FastLED.show();
    delay(150);
  }

  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    leds[dot].setRGB(0, 0, 0);
    FastLED.show();
    delay(150);
  }
  }

  void orangeLed()
  {
  for (int dot = (NUM_LEDS - 1) ; dot >= 0 ; dot--)
  {
    leds[dot].setRGB(255, 140, 0);
  }
  FastLED.show();
  delay(150);

  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    leds[dot].setRGB(0, 0, 0);
  }
  FastLED.show();
  delay(150);
  }

  void redLed()
  {
  for (int dot = (NUM_LEDS - 1) ; dot >= 0 ; dot--)
  {
    leds[dot].setRGB(178, 34, 34);
  }
  FastLED.show();
  delay(150);

  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    leds[dot].setRGB(0, 0, 0);
  }
  FastLED.show();
  delay(150);
  } */

#define FASTLED_RGBW
#include <FastLED.h>

#define NUM_LEDS 3
#define BRIGHTNESS 5
#define LED_TYPE SK6812
#define COLOR_ORDER GRB

const int stripPin = 2;
CRGB leds[NUM_LEDS];

unsigned long lastBlinkTime = 0;
const long blinkInterval = 100;
bool ledsOn = false;

void setupStrip() {
  FastLED.addLeds<LED_TYPE, stripPin, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void blinkStrip(CRGB color) {
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = currentMillis;
    ledsOn = !ledsOn; // Toggle the state of the LEDs

    if (ledsOn) {
      // Turn on all LEDs to the specified color
      for (int ledNum = 0; ledNum < NUM_LEDS; ledNum++)
      {
        leds[ledNum] = color;
      }
      FastLED.show();
    } else {
      for (int ledNum = 0; ledNum < NUM_LEDS; ledNum++)
      {
        leds[ledNum] = CRGB::Black;
      }
      FastLED.show();
    }

  }
}
