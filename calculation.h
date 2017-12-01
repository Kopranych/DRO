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
#define PERFECT_FREQ 1000000000L
#define VALUE_LIMIT 1023


//typedef enum{ //крутим карусель 
//    mode1,
//    mode2,
//    mode3,
//    mode4,
//    mode5,
//    mode6
//}PERFECT_FREQ;
//PERFECT_FREQ Freq;




extern unsigned long int freq_max, freq_min;

//
unsigned int calcul_freq(unsigned long freq_meas, unsigned int DAC_value);
unsigned long summa_array(unsigned long buffer[]);

// 
unsigned int rounding(float n);
