#include <Arduino.h>
#include <FastLED.h>
#include <math.h>

#define NUM_LEDS 9
#define LED_PIN 9

int HUE = 0;
int SAT = 255;
int VAL = 255;

bool brightnessIncreasing = true;

float indexInc = 0;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
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
  // indexDark = fmod(indexInc,NUM_LEDS);
  if (indexInc > NUM_LEDS - 1) {
    indexInc = 0;
  }
  

  Serial.println("-- -- -- -- -- -- -- --");
  Serial.println("");
  Serial.print("indexInc: ");
  Serial.println(indexInc);


  for (float i = 0; i < NUM_LEDS; i++) {
    float distFromIndexDark;
    if (i == indexInc) {
      distFromIndexDark = 0;
    } else {
      float distA = abs(i - indexInc);
      float distB = NUM_LEDS - abs(i - indexInc);
      distFromIndexDark = min(distA, distB);
    }
    
    // } else if (i > indexInc) {
    //   Serial.println("i > indexInc");
    //   distFromIndexDark = i - indexInc;
    // } else if (i < indexInc) {
    //   Serial.println("i < indexInc");
    //   distFromIndexDark = abs(i - indexInc);
    // }

    long int adjVal = min(pow(distFromIndexDark, log(255)), 255);
    int index = i;

    long int adjHue = HUE + (i * 5);

    leds[index].setHSV(adjHue,SAT,adjVal);

    Serial.print(i);
    Serial.print(" - distFromIndexDark: ");
    Serial.print(distFromIndexDark);
    Serial.print(" - ");
    Serial.println(adjVal);
  }

  FastLED.show();
  delay(10);
}