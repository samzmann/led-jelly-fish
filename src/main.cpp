#include <Arduino.h>
#include <FastLED.h>
#include <math.h>

#define NUM_LEDS_VERT 8
#define LED_PIN_VERT 9

#define NUM_LEDS_HORI 18
#define LED_PIN_HORI 10

int HUE = 0;
int SAT = 255;
int VAL = 255;

bool brightnessIncreasing = true;

float indexInc = 0;
float horizontalPulse = 0;
bool incHorizontalPulse = false;

CRGB ledsVert[NUM_LEDS_VERT];
CRGB ledsHori[NUM_LEDS_HORI];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, LED_PIN_VERT, GRB>(ledsVert, NUM_LEDS_VERT);
  FastLED.addLeds<WS2812B, LED_PIN_HORI, GRB>(ledsHori, NUM_LEDS_HORI);
}

void loop() {

  // if ( VAL >= 255) {
  //   brightnessIncreasing = false;
  // } else if (VAL <= 0) {
  //   brightnessIncreasing = true;
  // }

  // if (brightnessIncreasing) {
  //   VAL += 1;
  // } else {
  //   VAL -= 1;
  // }

  HUE += 1;

  indexInc += 0.1;
  // indexDark = fmod(indexInc,NUM_LEDS_VERT);
  if (indexInc > NUM_LEDS_VERT) {
    indexInc = 0;
  }

  if (indexInc > NUM_LEDS_VERT - 3) {
    incHorizontalPulse = true;
  }

  if (incHorizontalPulse) {
    horizontalPulse += 1;
  } else {
    horizontalPulse -= 1;
  }

  if (horizontalPulse >= 255) {
    incHorizontalPulse = false;
  }
  

  Serial.println("-- -- -- -- -- -- -- --");
  Serial.println("");
  Serial.print("indexInc: ");
  Serial.println(indexInc);


  for (float i = 0; i < NUM_LEDS_VERT; i++) {
    float distFromIndexDark;
    if (i == indexInc) {
      distFromIndexDark = 0;
    } else {
      float distA = abs(i - indexInc);
      float distB = NUM_LEDS_VERT - abs(i - indexInc);
      distFromIndexDark = min(distA, distB);
    }

    long int adjVal = 255 - (distFromIndexDark * (255 / (NUM_LEDS_VERT /2 )));
    int index = i;

    long int adjHue = HUE + (i * 5);

    ledsVert[index].setHSV(adjHue,SAT,adjVal);
  }

  Serial.print("horizontalPulse: ");
  Serial.print(horizontalPulse);

  for (int i = 0; i < NUM_LEDS_HORI; i++) {

    long int adjVal = max(horizontalPulse, 0);

    ledsHori[i].setHSV(HUE,SAT,adjVal);
  }

  FastLED.show();
  delay(25);
}