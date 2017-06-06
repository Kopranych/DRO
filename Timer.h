/* 
 * File:   Timer.h
 * Author: Kopranov_IN
 *
 * Created on 20 ???? 2016 ?., 9:24
 */

#include <p24fj256da210.h>

#define PORT_T1 PORTC
#define TRIS_T1 TRISC
#define PORT_T2 PORTF
#define TRIS_T2 TRISF
#define SYSCLK 100000
#define t1 0.5
#define PREG SYSCLK/2*t1/256
#define DELAY 2
#define MEASURTI 0xF000//time measurment






void init_timer1(void);//инициализация таймера 1
void init_timer23(void);//инициализация таймеров 2/3
void init_timer45(void);
void start_timer1_23_45(void);//start timer1 and timer2/3
void mapping_pin_timer2RP0(void);//remap pin timer2 to RP0
void mapping_pin_timer4RP0(void);
