#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <stdio.h>

#define LED_PIN 25

void core1_task() {
    int seconds = 0;
    while (true) {
        sleep_ms(1000);
        seconds++;
        printf("Core 1 running — %d seconds elapsed\n", seconds);
    }
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    multicore_launch_core1(core1_task);  // Core 1 starts here

    while (true) {  // Core 0 blinks LED
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        sleep_ms(200);
    }
}
