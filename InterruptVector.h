/* 
 * File:   InterruptVector.h
 * Author: Kopranov_IN
 *
 * Created on 19 ???? 2016 ?., 13:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256ga110.h>
#include "Timer.h"



int flag_interrupt = 0;
unsigned long int value_freqL = 0, value_freqH = 0;



void _ISRFAST _T1Interrupt(void)//прерывание по таймеру 1
{
    _T1IF=0;//сбросили флаг прерывания
    value_freqL = TMR2;//сохранили значение счетчиков
    value_freqH = TMR3;

//    timer3 = TMR3;
    TMR2 = 0;//сбросили 
    TMR3 = 0;//счетчики
    flag_interrupt = 1;//зажгли флаг для обработки значений счетчиков
}

//void __attribute__((__interrupt__)) _T1Interrupt(void);//
//void _ISRFAST _T4Interrupt(void)//прерывание по таймеру 4 
//{}//необходимо настроить на срабатывание этого таймера после 11-12 секунд подсчета
//в нем обнулять значения счетчиков TMR1-TMR3 получится избежать не корректного 
//значения частоты при пропадании сигнала с GPS
