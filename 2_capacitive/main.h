#include "mbed.h"                 // Load the mbed libraries

Serial pc(USBTX, USBRX); // Communicate back to the computer

// The LED that we want to control
DigitalOut led(LED1);

// Moisture sensor is attached to pin A0, and is an 'analog' sensor (can have a range from 0..1)
AnalogIn moisture(A0);

void measure_moisture() {
    while (1) {

        // YOUR CODE HERE

    }
}


// This is your main function
int main() {
    pc.baud(115200);


    // We don't want to block our whole program when reading the moisture sensor, so you can spin up a new 'thread'
    Thread t;
    t.start(&measure_moisture);

    while (1) {
        wait(osWaitForever);
    }
}
