/* 
 * File:   calculation.h
 * Author: Kopranov_IN
 *
 * Created on 28 ???? 2016 ?., 13:10
 */

#include <stdio.h>
#include <math.h>

#define Fmax //
#define Fmin //
#define N 10// 
#define PERFECT_FREQ 10000000L
#define VALUE_LIMIT 1023

extern unsigned long int freq_max, freq_min;

//
unsigned int calcul_freq(unsigned long int freq_meas, unsigned int DAC_value);

// 
unsigned int rounding(float n);
