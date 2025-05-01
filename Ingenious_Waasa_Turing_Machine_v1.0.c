#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

const int LED_PIN = 25;
const int SENSOR_PIN = 26;
const int PUMP_PIN = 10;

const int DRY = 1600;

void setup()
{
    stdio_init_all();
    adc_init();
    adc_gpio_init(SENSOR_PIN);
    adc_select_input(0);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(PUMP_PIN);
    gpio_set_dir(PUMP_PIN, GPIO_OUT);
}

uint16_t read_sensor()
{
    return adc_read();
}

void loop()
{
    while (true)
    {
        uint16_t moistvalue = read_sensor();

        if (moistvalue >= DRY) {
            gpio_put(LED_PIN, 1);
            
            gpio_put(PUMP_PIN, 0);
            sleep_ms(3000);
            gpio_put(PUMP_PIN, 1);
            
            gpio_put(LED_PIN, 0);
        }
        // 1 hour 3600000
        sleep_ms(3600000);
    }
}

int main()
{
    setup();
    loop();
    return 0;
}