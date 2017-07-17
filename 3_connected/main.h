#include "mbed.h"
#include "easy-connect.h"                   // Connectivity driver
#include "security.h"                       // Security certificate
#include "simple-mbed-client.h"             // Load mbed Client

static EventQueue eventQueue;               // An event queue
static Thread eventThread;                  // An RTOS thread to process events in

SimpleMbedClient client;

// YOUR CODE HERE

// Use the built-in LED as a status LED
DigitalOut statusLed(LED1);
int        statusLedBlinkId;    // Callback ID

void blink_builtin_led() {
    statusLed = !statusLed;
}

void registered() {
    // When we registered with mbed Cloud, keep solid
    eventQueue.cancel(statusLedBlinkId);

    statusLed = BUILTIN_LED_ON;

    printf("Registered\r\n");
}

int main(int, char**) {
    // Set the baud rate that is used to communicate back to the computer to 115,200
    Serial pc(USBTX, USBRX);
    pc.baud(115200);

    pc.printf("Hello world\n");

    // Using an event queue is a very useful abstraction around many microcontroller 'problems', like dealing with ISRs
    // see https://developer.mbed.org/blog/entry/Simplify-your-code-with-mbed-events/
    eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

    // Blink the built-in LED every 1000ms. After registering we'll blink every 300ms.
    statusLedBlinkId = eventQueue.call_every(1000, &blink_builtin_led);

    // Read the moisture data every second
    eventQueue.call_every(1000, &update_moisture);

    printf("whuuu\n");

    NetworkInterface* network = easy_connect(true);
    if (!network) {
        printf("Connect to internet failed... See serial output.\n");
        return 1;
    }

    struct MbedClientOptions opts = client.get_default_options();
    opts.DeviceType = "dsa-sensor";
    if (!client.setup(opts, network)) {
        printf("Setting up mbed_client failed...\n");
        return 1;
    }

    // @todo, move to event queue
    client.on_registered(&registered);

    wait(osWaitForever);
}
