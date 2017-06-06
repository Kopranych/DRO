/* 
 * File:   calculation.h
 * Author: Kopranov_IN
 *
 * Created on 28 ???? 2016 ?., 13:10
 */

#include <stdio.h>
#include <math.h>

#define Fmax 1250006// ????. ??????? ????
#define Fmin 1250000//???. ??????? ????
#define N 10// ??????????? ???
#define PERFECT_FREQ 1250003
#define VALUE_LIMIT 1024
#define Range_Freq (Fmax-Fmin) 
#define Range_Volt 5
#define STEP_Volt Range_Volt/pow(2, N)
#define STEP_VoltFreq 0.833333333


//?????????? ????????, ?????????? ???????
unsigned int calcul_freq(unsigned long int freq_meas, unsigned int DAC_value);

// ?????????? ?? ?????? ????????
unsigned int rounding(float n);
