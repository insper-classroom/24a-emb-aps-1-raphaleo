#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "arq.h"

void build_array(int arr[100]) {
    uint64_t start_us = to_us_since_boot(get_absolute_time());
    srand(start_us);
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 4;
    }
}

void display_diff(int diff){
    if (diff == 0){
        gpio_put(LED_DIFF_Y, 1);
        gpio_put(LED_DIFF_G, 0);
        gpio_put(LED_DIFF_R, 0);
    } else if (diff == 1){
        gpio_put(LED_DIFF_Y, 1);
        gpio_put(LED_DIFF_G, 1);
        gpio_put(LED_DIFF_R, 0);
    } else if (diff == 2){
        gpio_put(LED_DIFF_Y, 1);
        gpio_put(LED_DIFF_G, 1);
        gpio_put(LED_DIFF_R, 1);
    }
}

void set_diff(int flag){
    diff = flag;
}

void playtone(int freq, int duration) {
    int period = 1000000 / freq;
    int cycles = duration * freq / 1000;
    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(period / 2);
        gpio_put(BUZZER, 0);
        sleep_us(period / 2);
    }
}

//void display(int num) {
//    if (num<0){
//        num = 0;
//    }
//    for (int i = 0; i < 8; i++) {
//        int state = chars[num][i];
//        gpio_put(display_pins[i], state);
//    }
//}

void game_over(){
    for (int i = 4; i > 0; i--) {
        gpio_put(LED_Y, 1);
        gpio_put(LED_B, 1);
        gpio_put(LED_G, 1);
        gpio_put(LED_R, 1);
        playtone(1000+100*i, 100);
        gpio_put(LED_Y, 0);
        gpio_put(LED_B, 0);
        gpio_put(LED_G, 0);
        gpio_put(LED_R, 0);
        sleep_ms(100);
    }


}

void start(void){
    gpio_put(LED_Y, 1);
    playtone(1000, 100);
    sleep_ms(50);
    gpio_put(LED_Y, 0);
    sleep_ms(50);
    gpio_put(LED_B, 1);
    playtone(1100, 100);
    sleep_ms(50);
    gpio_put(LED_B, 0);
    sleep_ms(50);
    gpio_put(LED_G, 1);
    playtone(1200, 100);
    sleep_ms(50);
    gpio_put(LED_G, 0);
    sleep_ms(50);
    gpio_put(LED_R, 1);
    playtone(1300, 100);
    sleep_ms(50);
    gpio_put(LED_R, 0);
    sleep_ms(50);
    stage = 1;
    
}



void btn_callback(uint gpio, uint32_t events) {
    if (gpio == ON_OFF){
        BTN_ON_OFF = !BTN_ON_OFF;
    }
    if (gpio == BTN_Y && start_flag) {
        BTN_Y_FLAG = 1;
    } else if (gpio == BTN_B && start_flag) {
        BTN_B_FLAG = 1;
    } else if (gpio == BTN_G && start_flag) {
        BTN_G_FLAG = 1;
    } else if (gpio == BTN_R && start_flag) {
        BTN_R_FLAG = 1;
    } else if (gpio == BTN_DIFF) {
        BTN_DIFF_FLAG += 1;
        if (BTN_DIFF_FLAG == 3){
            BTN_DIFF_FLAG = 0;
        }
    }
}