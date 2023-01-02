#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>

/*   (SND_SEL) PB0      PA0 --
     (LED_SEL) PB1      PA1 --
     (VIB_SEL) PB2      PA2 --
               PB3      PA3 --
               PB4      PA4 --
        (MOSI) PB5      PA5 --
        (MISO) PB6      PA6 --
         (SCK) PB7      PA7 --
               RESET   AREF
               VCC      GND
               GND     AVCC
               XTAL2    PC7
               XTAL1    PC6 --
         (RX0) PD0      PC5 --
         (TX0) PD1      PC4 --
         (RX1) PD2      PC3 --
         (RX2) PD3      PC2 --
               PD4      PC1 --
         (VIB) PD5      PC0 --
         (LED) PD6      PD7 --

    - 16mhz oscillator needs to be between XTAL2 and XTAL1, with 22pF caps to GND
    - speaker is connected to DFPlayerMini alone
*/

#define SND_SEL 0
#define LED_SEL 1
#define VIB_SEL 2

#define VIB_PIN 13
#define LED_PIN 14


DFRobotDFPlayerMini player;
Adafruit_NeoPixel leds(4, LED_PIN, NEO_GRB + NEO_KHZ800);

uint8_t sound = 0xff;
uint8_t light = 0xff;
uint8_t motor = 0xff;
uint8_t tickCnt = 0;
uint16_t motorTimeout = 0;
uint16_t lightTimeout = 0;

void setStripLeft(uint8_t r, uint8_t g, uint8_t b) {
    leds.setPixelColor(2, r, g, b);
    leds.setPixelColor(3, r, g, b);
}

void setStripRight(uint8_t r, uint8_t g, uint8_t b) {
    leds.setPixelColor(0, r, g, b);
    leds.setPixelColor(1, r, g, b);
}

void setStrip(uint8_t r, uint8_t g, uint8_t b) {
    leds.setPixelColor(0, r, g, b);
    leds.setPixelColor(1, r, g, b);
    leds.setPixelColor(2, r, g, b);
    leds.setPixelColor(3, r, g, b);
}


/** Called every 10ms, updates the effects in progress for lights and vibrating motor.
 */
void tick() {
    if (motorTimeout > 0) {
        if (--motorTimeout == 0)
            analogWrite(VIB_PIN, 0);
    }
    if (lightTimeout > 0) {
        if (--lightTimeout == 0) {
            // turn leds off
            leds.clear();
            if (light == 15) // go for kaboom
                player.playFolder(1, 16);
        } else {
            switch (light) {
                case 8: // yellow flashes
                    if ((lightTimeout / 50) % 2)
                        setStrip(0, 0, 0); 
                    else 
                        setStrip(255, 255, 0); 
                    break;
                case 9: // red flashes
                    if ((lightTimeout / 50) % 2)
                        setStrip(0, 0, 0); 
                    else 
                        setStrip(255, 0, 0); 
                    break;
                case 10: // blue flashes
                    if ((lightTimeout / 50) % 2)
                        setStrip(0, 0, 0); 
                    else 
                        setStrip(0, 0, 255); 
                    break;
                case 11: // yellow alternating
                    if ((lightTimeout / 50) % 2) {
                        setStripLeft(0, 0, 0); 
                        setStripRight(255, 255, 0); 
                    } else { 
                        setStripRight(0, 0, 0); 
                        setStripLeft(255, 255, 0); 
                    }
                    break;
                case 12: // red alternating
                    if ((lightTimeout / 50) % 2) {
                        setStripLeft(0, 0, 0); 
                        setStripRight(255, 0, 0); 
                    } else { 
                        setStripRight(0, 0, 0); 
                        setStripLeft(255, 0, 0); 
                    }
                    break;
                case 13: // blue alternating
                    if ((lightTimeout / 50) % 2) {
                        setStripLeft(0, 0, 0); 
                        setStripRight(0, 0, 255); 
                    } else { 
                        setStripRight(0, 0, 0); 
                        setStripLeft(0, 0, 255); 
                    }
                    break;
                case 14: // red / blue alternating
                    if ((lightTimeout / 30) % 2) {
                        setStripLeft(0, 0, 0); 
                        setStripRight(0, 0, 255); 
                    } else { 
                        setStripRight(0, 0, 0); 
                        setStripLeft(255, 0, 0); 
                    }
                    break;
                case 15: { // countdown and kaboom
                    uint8_t id = lightTimeout / 100;
                    leds.setPixelColor(id, lightTimeout % 100, 0, 0);   
                    break;
                }
            }
        }
        leds.show();            
    }


}

uint8_t getSelection() {
    // 0-7 from the top of the chip
    for (uint8_t i = 24; i < 32; ++i)
        if (digitalRead(i) == LOW)
            return i - 24;
    // 8-15 from the bottom of the chip
    for (uint8_t i = 15; i < 23; ++i)
        if (digitalRead(i) == LOW)
            return i - 7;
    return 0xff;
}

bool checkEffectUpdate(uint8_t & effect) {
    tick();
    delay(10);
    uint8_t v = getSelection();
    if (v == effect) {
        return false;
    } else {
        effect = v;
        return true;
    }
}

void updateSound() {
    if (sound != 0xff)
        player.playFolder(1, sound);
    else
        player.stop();
}

void updateLight() {
    Serial.print("Light value:");
    Serial.println(light);
    switch (light) {
        case 0:
            setStrip(0, 0, 0);
            break;
        case 1:
            setStrip(255, 0, 0);
            break;
        case 2:
            setStrip(0, 255, 0);
            break;
        case 3: 
            setStrip(0, 0, 255); 
            break;
        case 4: 
            setStrip(255, 0, 255); 
            break;
        case 5: 
            setStrip(0, 255, 255); 
            break;
        case 6: 
            setStrip(255, 255, 0);
            break;
        case 7:
            setStrip(255, 255, 255);
            break;
        case 15:
            setStrip(100, 0, 0);
            lightTimeout = 400; // 4 secconds till detonation
            return;
        case 0xff:
            setStrip(0,0,0);
        default: // effects
            break; 
    }
    lightTimeout = 60 * 100; // 60 seconds
}

void updateMotor() {
    Serial.print("Motor value:");
    Serial.println(motor);
    if (motor == 0xff) {
        analogWrite(VIB_PIN, 0);
    } else if (motor == 15) {
        // TODO this might need something more
        analogWrite(VIB_PIN, 128);
        //analogWrite(VIB_PIN, motor * 16);
        //analogWrite(VIB_PIN, 128);
        motorTimeout = motor * 10; // max 1.5 seconds
    } else {
        player.playFolder(2, motor);
    }
}


void setup() {
    for (uint8_t i = 24; i < 32; ++i)
        pinMode(i, INPUT_PULLUP);
    for (uint8_t i = 15; i < 23; ++i)
        pinMode(i, INPUT_PULLUP);
    // the cables are input by default so that we can't short two cables together
    pinMode(SND_SEL, INPUT);
    pinMode(LED_SEL, INPUT);
    pinMode(VIB_SEL, INPUT);
    
    leds.begin();
    leds.setPixelColor(3, 0, 64, 0);
    leds.show();
    pinMode(VIB_PIN, OUTPUT);
    analogWrite(VIB_PIN, 0);

    Serial.begin(115200);
    Serial1.begin(9600);
    delay(250);
    leds.setPixelColor(2, 0, 128, 0);
    leds.show();
    Serial.println();
    Serial.println(F("OH HAI!"));
    delay(250);
    leds.setPixelColor(1, 0, 196, 0);
    leds.show();
    delay(250);
    if (!player.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Failed to initialize DFPlayer"));
        if (!player.available()) {
            Serial.println(F("Player not available"));
        }
        leds.setPixelColor(0, 255, 0, 0);
        leds.show();
        // TODO should we restart at this stage? 
    } else {
        Serial.println(F("DFPLayer initialized"));
        player.disableLoopAll();
        player.disableLoop();
        player.volume(0x12);
        leds.setPixelColor(0, 0, 255, 0);
        leds.show();
    }
    lightTimeout = 100; // 1 second;
}

void loop() {
    pinMode(SND_SEL, OUTPUT);
    digitalWrite(SND_SEL, LOW);
    if (checkEffectUpdate(sound)) 
        updateSound();
    pinMode(SND_SEL, INPUT);
    
    pinMode(LED_SEL, OUTPUT);
    digitalWrite(LED_SEL, LOW);
    if (checkEffectUpdate(light))
        updateLight();
    pinMode(LED_SEL, INPUT);
    
    pinMode(VIB_SEL, OUTPUT);
    digitalWrite(VIB_SEL, LOW);
    if (checkEffectUpdate(motor))
        updateMotor();
    pinMode(VIB_SEL, INPUT);
}