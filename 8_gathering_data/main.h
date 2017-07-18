#include "mbed.h"        // Load the mbed libraries
#include "ADXL345_I2C.h" // Accelerometer library
#include <sstream>

Serial pc(USBTX, USBRX);

static EventQueue eventQueue; // An event queue
static Thread eventThread;    // An RTOS thread to process events in

ADXL345_I2C accelerometer(D14, D15);

// YOUR CODE HERE
void start_measuring() {
    printf("Start reading data\n");

    std::stringstream x;
    std::stringstream y;
    std::stringstream z;

    int readings[3] = { 0, 0, 0 };

    int intervals = 3 * 30; // number of intervals (30 measurements x 3 seconds)
    int timeout = 33;       // ms. timeout between measuring

    for (size_t ix = 0; ix < intervals; ix++) {
        accelerometer.getOutput(readings);

        x << readings[0];
        x << ",";

        y << readings[1];
        y << ",";

        z << readings[2];
        z << ",";

        wait_ms(timeout);
    }

    printf("Done reading data\n");
    printf("X,%s\nY,%s\nZ,%s\n", x.str().c_str(), y.str().c_str(), z.str().c_str());
}

void timeout_start()
{
    printf("Start measuring in 5 seconds...\n");

    eventQueue.call_in(5000, &start_measuring);
}

// This is your main function
int main()
{
    pc.baud(115200);

    // Using an event queue is a very useful abstraction around many microcontroller 'problems', like dealing with ISRs
    // see https://developer.mbed.org/blog/entry/Simplify-your-code-with-mbed-events/
    eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

    // Create an 'interrupt', this is an object that can fire whenever state changes
    InterruptIn btn(USER_BUTTON);
    btn.fall(eventQueue.event(&timeout_start));

    // These are here to test whether any of the initialization fails. It will print the failure
    if (accelerometer.setPowerControl(0x00)) {
        printf("didn't intitialize power control\n");
        return 0;
    }
    // Full resolution, +/-16g, 4mg/LSB.
    wait(.001);

    if (accelerometer.setDataFormatControl(0x0B)) {
        printf("didn't set data format\n");
        return 0;
    }
    wait(.001);

    // 3.2kHz data rate.
    if (accelerometer.setDataRate(ADXL345_3200HZ)) {
        printf("didn't set data rate\n");
        return 0;
    }
    wait(.001);

    // Measurement mode.
    if (accelerometer.setPowerControl(MeasurementMode)) {
        printf("didn't set the power control to measurement\n");
        return 0;
    }

    printf("Accelerometer is initialized!\n");

    while (1) {
        wait(osWaitForever);
    }
}
