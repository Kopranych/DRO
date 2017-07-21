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



int flag_tmr1 = 0, count_t = 0, flag_interrupt, coun_tmr2, count_timer = 0;
unsigned long int value_freqL = 0, value_freqH = 0;



//void _ISRFAST _T1Interrupt(void)
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)//���������� �� ������� 1
{
    
//    value_freqL = TMR2;//��������� �������� ���������
//    value_freqH = TMR3;
//    coun_tmr2++;
    value_freqL = TMR4;
    value_freqH = TMR5;
    
 //   coun_tmr2 = 0;
    TMR4 = 0;
    TMR5 = 0;
    flag_tmr1 = 1;
    TMR1 = 0;
//    invers_LED_SYNH();
    _T1IF=0;//�������� ���� ����������
//    timer3 = TMR3;
//    TMR2 = 0;//�������� 
//   TMR3 = 0;//��������
//    flag_interrupt = 1;//������ ���� ��� ��������� �������� ���������
    count_timer++;  
}

//void _ISRFAST _T3Interrupt(void)//���������� �� ������� 1
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    _T3IF=0;
    TMR1 = 0;
    flag_interrupt = 1;
}

//void _ISRFAST _T2Interrupt(void)//���������� �� ������� 1
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    coun_tmr2++;
    TMR2 = 0;
    _T2IF=0;
//    flag_interrupt = 1;
}

void __attribute__((interrupt, auto_psv)) _T4Interrupt(void)
{
    value_freqL = TMR1;
    value_freqH = coun_tmr2;
    TMR1 = 0;
    coun_tmr2 = 0;
    TMR4 = 0;
    _T4IF=0;
    flag_interrupt = 1;
}

//void __attribute__((__interrupt__)) _T1Interrupt(void);//

//void _ISRFAST _T4Interrupt(void)//���������� �� ������� 4 
//{}//���������� ��������� �� ������������ ����� ������� ����� 11-12 ������ ��������
//� ��� �������� �������� ��������� TMR1-TMR3 ��������� �������� �� ����������� 
//�������� ������� ��� ���������� ������� � GPS
