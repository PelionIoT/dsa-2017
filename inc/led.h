#ifndef CONNECTED_LIGHTS_LED_H_
#define CONNECTED_LIGHTS_LED_H_

#include "mbed.h"
#include "ChainableLED.h"

class AnodeLED {
public:
    AnodeLED(PinName red_pin, PinName green_pin, PinName blue_pin) {
        red_led   = new PwmOut(red_pin);
        green_led = new PwmOut(green_pin);
        blue_led  = new PwmOut(blue_pin);
    }

    ~AnodeLED() {
        delete red_led;
        delete green_led;
        delete blue_led;
    }

    void setColorRGB(uint8_t red, uint8_t green, uint8_t blue) {
        red_led->write(1.0f - static_cast<float>(red) / 255.0f);
        green_led->write(1.0f - static_cast<float>(green) / 255.0f);
        blue_led->write(1.0f - static_cast<float>(blue) / 255.0f);
    }

private:
    PwmOut* red_led;
    PwmOut* green_led;
    PwmOut* blue_led;
};

class CathodeLED {
public:
    CathodeLED(PinName red_pin, PinName green_pin, PinName blue_pin) {
        red_led   = new PwmOut(red_pin);
        green_led = new PwmOut(green_pin);
        blue_led  = new PwmOut(blue_pin);
    }

    ~CathodeLED() {
        delete red_led;
        delete green_led;
        delete blue_led;
    }

    void setColorRGB(uint8_t red, uint8_t green, uint8_t blue) {
        red_led->write(static_cast<float>(red) / 255.0f);
        green_led->write(static_cast<float>(green) / 255.0f);
        blue_led->write(static_cast<float>(blue) / 255.0f);
    }

private:
    PwmOut* red_led;
    PwmOut* green_led;
    PwmOut* blue_led;
};

#endif // CONNECTED_LIGHTS_LED_H_
