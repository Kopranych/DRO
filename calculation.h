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
#define PERFECT_FREQ 1000000000L
#define VALUE_LIMIT 1023
#define OVERFLOW 0xFFFFFFFF







extern unsigned long int freq_max, freq_min;

//
int calcul_freq(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq,  unsigned long Range_Freq, int count);
//unsigned long summa_array(unsigned long buffer[]);

// 
unsigned int rounding(float n);

double_long multiplication_x64(double_long value, unsigned int multiplier);

double_long subtraction(double_long first_value, double_long second_value);
