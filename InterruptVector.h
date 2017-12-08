/* 
 * File:   InterruptVector.h
 * Author: Kopranov_IN
 *
 * Created on 19 ???? 2016 ?., 13:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256da210.h>
#include "Timer.h"


#define FIFO_SIZE 5


int flag_tmr1 = 0, flag_tmr2 = 0, count_t = 0, flag_interrupt,\
        coun_tmr2, count_timer = 0;
unsigned long int value_freqL = 0, value_freqH = 0;
unsigned int high_bitnes_tmr45_count = 0;
unsigned int high_bitnes_tmr45 = 0;



//void _ISRFAST _T1Interrupt(void)
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)//прерывание по таймеру 1
{
    //сохранили значение счетчиков
    _T1IF=0;//сбросили флаг прерывания  
    
    flag_tmr1 = 1;
    TMR1 = 0;
//    value_freqL = TMR4;
//    value_freqH = TMR5;
//    TMR4 = 0;
//    TMR5 = 0;
    count_timer++;
    if(count_timer < FIFO_SIZE){
        value_freqL = TMR4;
        value_freqH = TMR5;
        high_bitnes_tmr45 = high_bitnes_tmr45_count;
        
    }else{
        value_freqL = TMR4;
        value_freqH = TMR5;
        high_bitnes_tmr45 = high_bitnes_tmr45_count;
        TMR4 = 0;
        TMR5 = 0;
        high_bitnes_tmr45_count = 0;
        count_timer = 0;
    }
      
}

//void _ISRFAST _T3Interrupt(void)//прерывание по таймеру 3
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    _T3IF=0;
    TMR1 = 0;
    flag_interrupt = 1;
}

//void _ISRFAST _T2Interrupt(void)//прерывание по таймеру 2
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    value_freqL = TMR4;
    value_freqH = TMR5;
    high_bitnes_tmr45 = high_bitnes_tmr45_count;
    //сбросили счетчики
    high_bitnes_tmr45_count = 0;
    TMR4 = 0;
    TMR5 = 0;
    TMR2 = 0;
    _T2IF = 0;
    flag_tmr2 = 1;
}

void __attribute__((interrupt, auto_psv)) _T4Interrupt(void)
{
    high_bitnes_tmr45_count++;
    _T4IF=0;//сбросили флаг прерывания   
}
//void __attribute__((__interrupt__)) _T1Interrupt(void);//

//void _ISRFAST _T4Interrupt(void)//прерывание по таймеру 4 
//{}//необходимо настроить на срабатывание этого таймера после 11-12 секунд подсчета
//в нем обнулять значения счетчиков TMR1-TMR3 получится избежать не корректного 
//значения частоты при пропадании сигнала с GPS
