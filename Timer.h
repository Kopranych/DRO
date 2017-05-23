/* 
 * File:   Timer.h
 * Author: Kopranov_IN
 *
 * Created on 20 ???? 2016 ?., 9:24
 */

#include <p24fj256ga110.h>

#define PORT_T1 PORTC
#define TRIS_T1 TRISC
#define PORT_T2 PORTF
#define TRIS_T2 TRISF
#define MEASURTI 9//time measurment






void init_timer1();//инициализация таймера 1
void init_timer23();//инициализация таймеров 2/3
void start_timer1_23();//start timer1 and timer2/3
void mapping_pin_timer2RP0();//remap pin timer2 to RP0
