#include "mbed.h"                 // Load the mbed libraries

// YOUR CODE HERE


// This is your main function
int main() {

    // Create an 'interrupt', this is an object that can fire whenever state changes
    InterruptIn btn(USER_BUTTON);
    // When the button 'falls' (gets pressed), execute the function
    btn.fall(&toggle_led);

    while (1) {
        wait(osWaitForever);
    }
}
