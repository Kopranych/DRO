
#include "calculation.h"



unsigned int calcul_freq(unsigned long int freq_meas, unsigned int DAC_value)
{
    float step = STEP_VoltFreq, step_v = STEP_Volt;       
    unsigned int shift;
    unsigned long int difference, ideal = PERFECT_FREQ;
//   unsigned long int f_perf = F_PERF;
//   freq_meas *= 256;//???? ???????????? ??????????? ??????? ???????? ?? 256
    if(freq_meas < ideal)
    {
        difference = ideal - freq_meas;//????????? ???????? ????????? ? ?????????? ???????
        shift = difference*step;//????????? ???????? ???????? ???????????? ??????????
        shift = shift/step_v;
        shift = rounding(shift);// ? ????????? ??? ?? ?????? 
        DAC_value += shift;//??????????? ??????? ???????? ??? ?? ???????? ????????
        
    }  
    else if(freq_meas > ideal)
    {
        difference = freq_meas - ideal;
        shift = difference*step;//????????? ???????? ???????? ???????????? ??????????
        shift = shift/step_v;
        shift = rounding(shift);
        DAC_value -= shift;
    }
    else if(freq_meas == ideal) DAC_value = DAC_value;
//???? DAC_value   
    if(DAC_value == VALUE_LIMIT) return (DAC_value - 1);
    else return DAC_value;   
}

unsigned int rounding(float n)// ?????????? ?? ?????? ????????
{
    unsigned int y = floor(n);
    if((n - y)>= 0.5) y++;
    return y;
}
