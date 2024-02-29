/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int ON_OFF = 28;

const int LED_Y = 14;
const int BTN_Y = 15;

const int LED_B = 2;
const int BTN_B = 3;

const int LED_G = 26;
const int BTN_G = 27;

const int LED_R = 16;
const int BTN_R = 17;

const int BUZZER = 7;


volatile int BTN_ON_OFF = 0;
volatile char BTN_Y_FLAG = 0;
volatile char BTN_B_FLAG = 0;
volatile char BTN_G_FLAG = 0;
volatile char BTN_R_FLAG = 0;


volatile int start_flag = 0;
volatile int sequence_flag = 0;


int sequence[100];

void build_array(int arr[100]) {
    uint64_t start_us = to_us_since_boot(get_absolute_time());
    srand(start_us);
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 4;
    }
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
    }
}



int main() {
    stdio_init_all();
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_init(LED_Y);
    gpio_init(LED_B);
    gpio_init(LED_G);
    gpio_init(LED_R);
    gpio_init(BTN_Y);
    gpio_init(BTN_B);
    gpio_init(BTN_G);
    gpio_init(BTN_R);
    gpio_init(ON_OFF);
    gpio_set_dir(ON_OFF, GPIO_IN);
    gpio_set_dir(LED_Y, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(BTN_Y, GPIO_IN);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_set_dir(BTN_G, GPIO_IN);
    gpio_set_dir(BTN_R, GPIO_IN);
    gpio_pull_up(BTN_Y);
    gpio_pull_up(BTN_B);
    gpio_pull_up(BTN_G);
    gpio_pull_up(BTN_R);
    gpio_pull_up(ON_OFF);
    gpio_set_irq_enabled_with_callback(BTN_Y, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_G, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_R, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(ON_OFF, GPIO_IRQ_EDGE_FALL, true);
    while (true) {
        
        if (BTN_ON_OFF){
            if (!sequence_flag){
            build_array(sequence);
            printf("\n Sequence: ");
            for (int i = 0; i < 100; i++) {
                printf("%d ", sequence[i]);
            }
            sequence_flag = 1;
            
        }
            if (!start_flag){
                start();
                start_flag = 1;
                sleep_ms(100);
            }
            if(BTN_Y_FLAG){
                BTN_Y_FLAG = 0;
                gpio_put(LED_Y, 1);
                playtone(1000, 100);
                //sleep_ms(50);
                gpio_put(LED_Y, 0);
            }
            if(BTN_B_FLAG){
                BTN_B_FLAG = 0;
                gpio_put(LED_B, 1);
                playtone(1100, 100);
                //sleep_ms(50);
                gpio_put(LED_B, 0);
            }
            if(BTN_G_FLAG){
                BTN_G_FLAG = 0;
                gpio_put(LED_G, 1);
                playtone(1200, 100);
                //sleep_ms(50);
                gpio_put(LED_G, 0);
            }
            if(BTN_R_FLAG){
                BTN_R_FLAG = 0;
                gpio_put(LED_R, 1);
                playtone(1300, 100);
                //sleep_ms(50);
                gpio_put(LED_R, 0);
            }
        } else{
            start_flag = 0;
            sequence_flag = 0;

            BTN_Y_FLAG = 0;
            BTN_B_FLAG = 0;
            BTN_G_FLAG = 0;
            BTN_R_FLAG = 0;
            gpio_put(LED_Y, 1);
            gpio_put(LED_B, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_R, 1);
            sleep_ms(1000);
            gpio_put(LED_Y, 0);
            gpio_put(LED_B, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_R, 0);
            sleep_ms(100);
        }
    }
}
