#ifndef ARQ_H
#define ARQ_H
#include <stdlib.h>
#include <stdio.h>


extern int ON_OFF;
extern int LED_Y;
extern int LED_G;
extern int LED_R;
extern int LED_B;
extern int BTN_Y;
extern int BTN_G;
extern int BTN_R;
extern int BTN_B;
extern int VIBRA_Y;
extern int VIBRA_G;
extern int VIBRA_R;
extern int VIBRA_B;
extern int BUZZER;
extern int BTN_DIFF;
extern int LED_DIFF_R;
extern int LED_DIFF_Y;
extern int LED_DIFF_G;
extern volatile int BTN_ON_OFF;
extern volatile char BTN_Y_FLAG;
extern volatile char BTN_G_FLAG;
extern volatile char BTN_R_FLAG;
extern volatile char BTN_B_FLAG;
extern volatile char BTN_DIFF_FLAG;
extern volatile int start_flag;
extern volatile int sequence_flag;
extern volatile int stage;
extern volatile int sequence_index;
extern volatile int current_index;
extern volatile int diff;

void build_array(int arr[100]);
void display_diff(int diff);
void set_diff(int flag);
void playtone(int freq, int duration);
void game_over();
void start(void);
void btn_callback(uint gpio, uint32_t events);

#endif 

