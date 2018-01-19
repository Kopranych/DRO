/* 
 * File:   calculation.h
 * Author: Kopranov_IN
 *
 * Created on 28 ???? 2016 ?., 13:10
 */

#include <stdio.h>
#include <math.h>
#include "fifo.h"
#include "led_dro.h"

#define Fmax //
#define Fmin //
#define N 10// 
#define VALUE_LIMIT 1023
#define OVERFLOW 0xFFFFFFFF

extern unsigned long int freq_max, freq_min;

/*
 * ������� ��������� ����������� �������� ��� ��� ������������� 
 * ���������� �������
 * ��������� double_long freq_meas - �������� ���������� �������
 * unsigned int DAC_value - ������� �������� ���
 * double_long perfect_freq - ����������� �������� �������
 * ����������  unsigned int �������� ��� ��� ������������� �������
 */
unsigned int calcul_freq(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq,  unsigned long Range_Freq);
//unsigned long summa_array(unsigned long buffer[]);

/*
 * ������� ���������� ���� float
 * ��������� float n ��������� ��� �� ������ �����
 * ���������� unsigned int ����������� �����
 */ 
unsigned int rounding(float n);

/*
 * ������� ��������� 64 - ���������� ����� ��������� �� ��� 32 - ��������� 
 * ��������� ��������: ��������� �� ���� 32-��������� ����������, � 
 * � ��������� ����� unsigned int 16 ���������
 * ���������� ��������� �� ���� 32-��������� ����������� ����������,
 * ������� ��� ����������� ���������� 64-��������� ���� �����
 * ��������� ���������� ������ ��� ���� ������� ��� ��������� 1023 ����� 88000 ������
 * ��� ������� ����������� fclk = 32��� ������������ ���������� ��������� �������� ����� t = 27,5�� 
*/
double_long multiplication_x64(double_long value, unsigned int multiplier);

/*
 * ������� ��������� 64-���������� ����� �� 64-���������� ����� ���
 * ��������� �� high-byte � low-byte ���������� � 32-��������� ������
 * ��������� ��� ��������� double_long first_value � double_long second_value
 * ��������� first_value - second_value
 * ���������� ��������� double_long ���������� ��������
 * �����������: ��������� ����������� ������ ����� first_value > second_value
 */
double_long subtraction(double_long first_value, double_long second_value);

/*
 * ������� ������� ���� ����� 64-��������� ���� �� �����
 * ��������� double_long first_value � double_long second_value
 * ��������� first_value/second_value
 * ���������� unsigned int �������� � ����������� ����� �������
 */
unsigned int division_64x(double_long first_value, double_long second_value);

/*
 * ������� �������� ���� ����� 64-��������� 
 * ��������� double_long first_value � double_long second_value
 * ��������� first_value+second_value
 * ���������� double_long 
 */
double_long addition_x64(double_long first_value, double_long second_value);

unsigned int calcul_freq_validate(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq);
