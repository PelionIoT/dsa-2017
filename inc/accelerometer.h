#ifndef ACCEL_H
#define ACCEL_H

#include "fxos8700cq.h"           // Driver for the accelerometer
#include "mbed_events.h"          // Event queue library

static FXOS8700CQ accel(PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1); // FRDM-K64F accelerometer
static InterruptIn accel_interrupt_pin(PTC13);  // Wait for an interrupt to happen...

static EventQueue accQueue;
static rtos::Thread accThread(osPriorityNormal, 1024);

class Accelerometer {
public:
    Accelerometer() : isFirstEvent(true) {}

    void start() {
        accThread.start(callback(this, &Accelerometer::start_thread));

        accel_interrupt_pin.fall(callback(this, &Accelerometer::interrupt));
        accel_interrupt_pin.mode(PullUp);

        accel_data = (SRAWDATA*)malloc(sizeof(SRAWDATA));
        magn_data = (SRAWDATA*)malloc(sizeof(SRAWDATA));

        accel.config_int();      // enabled interrupts from accelerometer
        accel.config_feature();  // turn on motion detection
        accel.enable();          // enable accelerometer
    }

    ~Accelerometer() {
        free(accel_data);
        free(magn_data);
    }

    void start_thread() {
        while (1) {
            accQueue.dispatch();
        }
    }

    void interrupt() {
        accel.clear_int();

        if (isFirstEvent) {
            isFirstEvent = false;
        }
        else {
            accQueue.call(cb);
        }
    }

    void change(Callback<void()> aCb) {
        cb = aCb;
    }

    SRAWDATA& read_accelerometer() {
        accel.get_data(accel_data, magn_data);
        return *accel_data;
    }

    SRAWDATA& read_magnetometer() {
        accel.get_data(accel_data, magn_data);
        return *magn_data;
    }

private:
    Callback<void()> cb;
    bool isFirstEvent;

    SRAWDATA* accel_data;
    SRAWDATA* magn_data;
};

#endif
