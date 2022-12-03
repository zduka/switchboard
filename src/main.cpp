#include <Adafruit_WS2801.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

/*         PB0      PA0 
           PB1      PA1
           PB2      PA2
           PB3      PA3
           PB4      PA4
    (MOSI) PB5      PA5
    (MISO) PB6      PA6
     (SCK) PB7      PA7
           RESET   AREF
           VCC      GND
           GND     AVCC
           XTAL2    PC7
           XTAL1    PC6
     (RXD) PD0      PC5
     (TXD) PD1      PC4
           PD2      PC3
           PD3      PC2
           PD4      PC1
           PD5      PC0
           PD6      PD7

    - 16mhz oscillator needs to be between XTAL2 and XTAL1, with 22pF caps to GND
    - avcc is connected to gnd

    - use software serial for dfplayer so that we keep hw serial for debugging
    - speaker is connected to DFPlayerMini alone
    - LED is connected to any pin it seems
    - motor is connected to a analog write capable pin 

    - 2 pins SW serial DFPlayer
    - 1 pin motor pwm
    - 1 pin LED
    - 3 pins = control wires
    - 2 pins = serial console
    - 3 pins = programmer
    - 20 pins are free for options

*/

#define LED_CLK 4
#define LED_DATA 3
#define BTN 0
#define NUM_LEDS 9

#define DEBOUNCE_THRESHOLD 2

#define MODE_RED 0
#define MODE_GREEN 1
#define MODE_BLUE 2
#define MODE_PINK 3
#define MODE_WARM_WHITE 4
#define MODE_RAINBOW 5
#define MODE_RAINBOW_CYCLE 6
#define MODE_OFF 7

Adafruit_WS2801 leds = Adafruit_WS2801(NUM_LEDS, LED_DATA, LED_CLK);
uint8_t mode = MODE_OFF;
uint8_t debounce;
uint8_t rainbowOffset = 0;

uint32_t RGB(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}

uint32_t HSV(uint8_t hue) {
    if (hue < 85) 
        return RGB(hue * 3, 255 - hue * 3, 0);
    hue -= 85;
    if (hue < 85)
       return RGB(255 - hue * 3, 0, hue * 3);
    hue -= 85;
    return RGB(0, hue * 3, 255 - hue * 3);
}

void fill(uint32_t color) {
    for (int i = 0; i < NUM_LEDS; ++i)
        leds.setPixelColor(i, color);
}

void rainbowFill(uint8_t offset) {
    uint8_t delta = 256 / NUM_LEDS;
    for (int i = 0; i < NUM_LEDS; ++i, offset += delta)
        leds.setPixelColor(i, HSV(offset));
}

void nextMode() {
    mode = (mode + 1) % 8;
    switch (mode) {
        case MODE_RED:
            fill(RGB(255, 0, 0));
            break;
        case MODE_GREEN:
            fill(RGB(0, 255, 0));
            break;
        case MODE_BLUE:
            fill(RGB(0, 0, 255));
            break;
        case MODE_PINK:
            fill(RGB(255, 53, 184));
            break;
        case MODE_WARM_WHITE:
            fill(RGB(255, 211, 64));
            break;
        case MODE_RAINBOW:
        case MODE_RAINBOW_CYCLE:
            rainbowFill(0);
            break;
        case MODE_OFF:
            fill(RGB(0,0,0));
            break;
    }
    leds.show();
}

void setup() {
    /*
    pinMode(BTN, INPUT_PULLUP);
    leds.begin();
    leds.show();
    nextMode();
    */
   pinMode(1, OUTPUT);
}

void loop() {
    digitalWrite(1, HIGH);
    delay(1000);
    digitalWrite(1, LOW);
    delay(1000);
    /*
  if (digitalRead(BTN) == LOW) {
      if (debounce > 0 && --debounce == 0) 
          nextMode();
  } else {
      debounce = DEBOUNCE_THRESHOLD;
  }
  delay(10);
  switch (mode) {
      case MODE_RAINBOW_CYCLE:
          ++rainbowOffset;
          rainbowFill(rainbowOffset);
          leds.show();
          break;

  }
  */
}
