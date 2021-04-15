#include <stdio.h>
#include <stdint.h>
#include <random>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../logo.hpp"
#include "../GFX.hpp"

int main() {

    //setup
    stdio_init_all();
    i2c_init(i2c1, 400000);                 //Initialize I2C on i2c1 port with 400kHz
    gpio_set_function(18, GPIO_FUNC_I2C);    //Use GPIO2 as I2C
    gpio_set_function(19, GPIO_FUNC_I2C);    //Use GPIO3 as I2C
    gpio_pull_up(18);                        //Pull up GPIO2
    gpio_pull_up(19);                        //Pull up GPIO3

    GFX oled(0x3C, D128x32, i2c1);          //Declare oled instance

    oled.display(logo);                     //Display bitmap

    std::default_random_engine en{};
    std::uniform_int_distribution<int> dist{1, 100};

    for (int i = 0; i < 3; ++i) {
        sleep_ms(1000);
        oled.clear();                       //Clear buffer
        oled.drawString(0, 0, "Raspberry Pico");
        oled.drawString(0, 10, "Oled Example");
        oled.drawProgressBar(0, oled.getHeight()-10, oled.getWidth(), 10, dist(en));
        oled.display();                     //Send buffer to the screen
    }

    for (int16_t x = 0; x < oled.getWidth(); ++x) {
        for (int16_t y = 0; y < oled.getHeight(); ++y) {
            sleep_ms(1000);
            oled.clear();
            oled.drawPixel(x, y);
            oled.display();
        }
    }

    return 0;
}