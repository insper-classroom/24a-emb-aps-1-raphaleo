/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "arq.h"


#define UART_ID uart0
#define BAUD_RATE 9600
int ON_OFF = 28;

int LED_Y = 14;
int BTN_Y = 15;
int VIBRA_Y = 16;

int LED_B = 2;
int BTN_B = 3;
int VIBRA_B = 4;

int LED_G = 26;
int BTN_G = 27;
int VIBRA_G = 5;

int LED_R = 17;
int BTN_R = 18;
int VIBRA_R = 19;

int BUZZER = 7;

int BTN_DIFF = 20;
int LED_DIFF_G = 22;
int LED_DIFF_Y = 21;
int LED_DIFF_R = 6;




//int display_pins[7] = {4, 5, 6, 8, 9, 10, 11};
//
//long chars[10][8] = {
//    {0, 1, 1, 1, 1, 1, 1, 1}, //0
//    {0, 0, 0, 1, 1, 0, 0, 0}, //1
//    {1, 0, 1, 1, 0, 1, 1, 1}, //2
//    {1, 0, 1, 1, 1, 1, 0, 1}, //3
//    {1, 1, 0, 1, 1, 0, 0, 1}, //4
//    {1, 1, 1, 0, 1, 1, 0, 1}, //5
//    {1, 1, 1, 0, 1, 1, 1, 1}, //6
//    {0, 0, 1, 1, 1, 0, 0, 0}, //7
//    {1, 1, 1, 1, 1, 1, 1, 1}, //8
//    {1, 1, 1, 1, 1, 1, 0, 1}  //9
//};


volatile int BTN_ON_OFF = 0;
volatile char BTN_Y_FLAG = 0;
volatile char BTN_B_FLAG = 0;
volatile char BTN_G_FLAG = 0;
volatile char BTN_R_FLAG = 0;
volatile char BTN_DIFF_FLAG = 0;


volatile int start_flag = 0;
volatile int sequence_flag = 0;
volatile int stage = 0;
volatile int sequence_index = 0;
volatile int current_index = 0;
volatile int diff = 0;






int main() {
    stdio_init_all();
    int note_delay = 150;
    int sequence[100];
    
    int points = -1;

    //sending data
    

    //receiving data
    //waiting to receive data


//    for (int i = 0; i < 8; i++) {
//        gpio_init(display_pins[i]);
//        gpio_set_dir(display_pins[i], GPIO_OUT);
//
//    }

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
    gpio_init(VIBRA_R);
    gpio_init(VIBRA_G);
    gpio_init(VIBRA_B);
    gpio_init(VIBRA_Y);

    gpio_init(LED_DIFF_G);
    gpio_init(LED_DIFF_Y);
    gpio_init(LED_DIFF_R);
    gpio_init(BTN_DIFF);

    gpio_set_dir(VIBRA_B, GPIO_OUT);
    gpio_set_dir(VIBRA_Y, GPIO_OUT);
    gpio_set_dir(VIBRA_G, GPIO_OUT);
    gpio_set_dir(VIBRA_R, GPIO_OUT);

    gpio_set_dir(BTN_DIFF, GPIO_IN);
    gpio_set_dir(LED_DIFF_G, GPIO_OUT);
    gpio_set_dir(LED_DIFF_Y, GPIO_OUT);
    gpio_set_dir(LED_DIFF_R, GPIO_OUT);

    gpio_set_dir(ON_OFF, GPIO_IN);
    gpio_set_dir(LED_Y, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(VIBRA_R, GPIO_OUT);
    gpio_set_dir(BTN_Y, GPIO_IN);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_set_dir(BTN_G, GPIO_IN);
    gpio_set_dir(BTN_R, GPIO_IN);
    gpio_pull_up(BTN_Y);
    gpio_pull_up(BTN_B);
    gpio_pull_up(BTN_G);
    gpio_pull_up(BTN_R);
    gpio_pull_up(ON_OFF);
    gpio_pull_up(BTN_DIFF);
    gpio_set_irq_enabled_with_callback(BTN_Y, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_G, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_R, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(ON_OFF, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_DIFF, GPIO_IRQ_EDGE_FALL, true);

    



    while (true) {
        //sent an 8bit number
        printf("%d\n", 2);
        if (uart_is_writable(UART_ID)){
            printf("Data sent: %d\n", 2);
            uart_putc_raw(UART_ID, (char) 2);
        }

//        display(points);
        display_diff(BTN_DIFF_FLAG);
        printf("dificuldade: %d\n", diff);

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
                set_diff(BTN_DIFF_FLAG);
                start();
                start_flag = 1;
                sleep_ms(500);
                stage = 1;
            } 
            if (stage == 1){
                for (int i = 0; i < sequence_index; i++) {
                    if (sequence[i] == 0) {
                        gpio_put(LED_Y, 1);
                        gpio_put(VIBRA_Y, 1);
                        playtone(1000, 100);
                        gpio_put(LED_Y, 0);
                        gpio_put(VIBRA_Y, 0);
                        sleep_ms(note_delay);
                    } else if (sequence[i] == 1) {
                        gpio_put(LED_B, 1);
                        gpio_put(VIBRA_B, 1);
                        playtone(1100, 100);
                        gpio_put(LED_B, 0);
                        gpio_put(VIBRA_B, 0);
                        sleep_ms(note_delay);
                    } else if (sequence[i] == 2) {
                        gpio_put(LED_G, 1);
                        gpio_put(VIBRA_G, 1);
                        playtone(1200, 100);
                        gpio_put(LED_G, 0);
                        gpio_put(VIBRA_G, 0);
                        sleep_ms(note_delay);
                    } else if (sequence[i] == 3) {
                        gpio_put(LED_R, 1);
                        gpio_put(VIBRA_R, 1);
                        playtone(1300, 100);
                        gpio_put(LED_R, 0);
                        gpio_put(VIBRA_R, 0);
                        sleep_ms(note_delay);
                    }
                    sleep_ms(100);
                }
                sleep_ms(100);
                stage = 2;
                
            }
            else if(stage == 2){
                if(BTN_Y_FLAG){
                    if (sequence[current_index] == 0) {
                        gpio_put(LED_Y, 1);
                        gpio_put(VIBRA_Y, 1);
                        playtone(1000, 100);
                        gpio_put(LED_Y, 0);
                        gpio_put(VIBRA_Y, 0);
                        sleep_ms(200);
                        current_index+=1;
                    } else {
                        game_over();
                        points = 0;
                        stage = 0;
                    }
                    BTN_Y_FLAG = 0;
                }
                if(BTN_B_FLAG){
                    if (sequence[current_index] == 1) {
                        gpio_put(LED_B, 1);
                        gpio_put(VIBRA_B, 1);
                        playtone(1100, 100);
                        gpio_put(LED_B, 0);
                        gpio_put(VIBRA_B, 0);
                        sleep_ms(200);
                        current_index+=1;
                    } else {
                        game_over();
                        points = 0;
                        stage = 0;
                    }
                    BTN_B_FLAG = 0;
                }
                if(BTN_G_FLAG){
                    if (sequence[current_index] == 2) {
                        gpio_put(LED_G, 1);
                        gpio_put(VIBRA_G, 1);
                        playtone(1200, 100);
                        gpio_put(LED_G, 0);
                        gpio_put(VIBRA_G, 0);
                        sleep_ms(200);
                        current_index+=1;
                    } else {
                        game_over();
                        points = 0;
                        stage = 0;
                    }
                    BTN_G_FLAG = 0;
                }
                if(BTN_R_FLAG){
                    if (sequence[current_index] == 3) {
                        gpio_put(LED_R, 1);
                        gpio_put(VIBRA_R, 1);
                        playtone(1300, 100);
                        gpio_put(LED_R, 0);
                        gpio_put(VIBRA_R, 0);
                        sleep_ms(200);
                        current_index+=1;
                    } else {
                        game_over();
                        points = 0;
                        stage = 0;
                    }
                    BTN_R_FLAG = 0;
                }
                if (current_index == sequence_index){
                    stage = 1;
                    sequence_index+=1+diff;
                    points++;
                    current_index = 0;
                    note_delay*=0.1*points+0.5*diff;
                    sleep_ms(1000);
                }
            }else{
                start_flag = 0;
                sequence_flag = 0;
                stage = 0;
                sequence_index = 0;
                current_index = 0;


                BTN_Y_FLAG = 0;
                BTN_B_FLAG = 0;
                BTN_G_FLAG = 0;
                BTN_R_FLAG = 0;
                BTN_ON_OFF = 0;
            }
        } else{
            start_flag = 0;
            sequence_flag = 0;
            stage = 0;
            sequence_index = 0;
            current_index = 0;

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
