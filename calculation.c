
#include "calculation.h"



unsigned int calcul_freq(unsigned long int freq_meas, unsigned int DAC_value)
{
    unsigned long Range_Freq = freq_max - freq_min;
    float step = Range_Freq/pow(2, N), shift;       
    unsigned long int difference, ideal = PERFECT_FREQ;

    if(freq_meas < ideal)
    {
        difference = ideal - freq_meas;//
        shift = difference/step;//
        shift = rounding(shift);// 
        DAC_value += (unsigned int)shift;//
        
    }  
    else if(freq_meas > ideal)
    {
        difference = freq_meas - ideal;
        shift = difference/step;//
        shift = rounding(shift);
        DAC_value -= (unsigned int)shift;
    }
    else if(freq_meas == ideal) DAC_value = DAC_value;

    if(DAC_value > VALUE_LIMIT) DAC_value = VALUE_LIMIT;
    return DAC_value;   
}

unsigned int rounding(float n)// ?????????? ?? ?????? ????????
{
    unsigned int y = floor(n);
    if((n - y)>= 0.5) y++;
    return y;
}
