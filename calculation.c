
#include "calculation.h"




unsigned int calcul_freq(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq,  unsigned long Range_Freq)
{
    unsigned int DAC_temp = DAC_value;
 //   unsigned long Range_Freq = freq_max - freq_min;
    double_long step;
    step.low_byte = rounding(Range_Freq/pow(2, N));
    step.high_byte = 0x0000;
    unsigned int shift;       
    double_long difference;
    
    if(step.low_byte < 1){
        step.low_byte = 1;
        DAC_value = calcul_freq_validate(freq_meas, DAC_temp,\
        perfect_freq);
    }
    if((freq_meas.high_byte <= perfect_freq.high_byte)\
            &(freq_meas.low_byte < perfect_freq.low_byte))
    {
        DAC_temp = calcul_freq_validate(freq_meas, DAC_temp,\
        perfect_freq);
        difference = subtraction(perfect_freq, freq_meas);//
        shift = division_64x(difference, step);//
        DAC_value += shift;//
        
        led_off(VD1);
        led_on(VD2);
//        if(DAC_value> 1023){
//            led_on(VD2);
//            DAC_value = 1023;
//        }
        
    }  
    else if((freq_meas.high_byte >= perfect_freq.high_byte)\
            &(freq_meas.low_byte > perfect_freq.low_byte))
    {
        DAC_temp = calcul_freq_validate(freq_meas, DAC_temp,\
        perfect_freq);
        difference = subtraction(freq_meas, perfect_freq);
        shift = division_64x(difference,step);//
//        shift = rounding(shift);
        DAC_value -= shift;
        
        led_on(VD1);
        led_off(VD2);
//        if(DAC_value> 1023){
//            led_on(VD2);
//            DAC_value = 1023;
//        }
    }
    else if((freq_meas.high_byte == perfect_freq.high_byte)\
            &(freq_meas.low_byte == perfect_freq.low_byte)){
        DAC_value = DAC_value;
        led_on(VD1);
        led_on(VD2);
    }
//    else
//    {
//        return -1;
//    }
//    if(DAC_value > VALUE_LIMIT){
//        
//        led_off(VD1);
//        led_off(VD2);
//        DAC_value = 512;
//    }
    return DAC_value;   
}

unsigned int rounding(float n)
{
    unsigned int y = floor(n);
    if((n - y)>= 0.5) y++;
    return y;
}

unsigned int calcul_freq_validate(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq)
{       
    perfect_freq = multiplication_x64(perfect_freq, DAC_value);
    DAC_value = division_64x(perfect_freq, freq_meas);
    return DAC_value;   
}

double_long addition_x64(double_long first_value, double_long second_value){
    
    unsigned long preview_low_value = 0;
    
    preview_low_value = first_value.low_byte;
    
    if((first_value.low_byte == 0) & (second_value.low_byte == 0))
    {
        first_value.low_byte = 0;
    }else{
        first_value.low_byte += second_value.low_byte;
        
        if(first_value.low_byte == 0){
            first_value.high_byte++;
        }else if(first_value.low_byte < preview_low_value){
            first_value.high_byte++;
        }
    }
    first_value.high_byte += second_value.high_byte;
    return first_value;
}

double_long multiplication_x64(double_long value, unsigned int multiplier){
    int i;
    double_long temp;
    temp.low_byte = 0;
    temp.high_byte = 0;
    unsigned long preview_low_value = 0;
    
    for(i = 0; i < multiplier; i++)
    {
        preview_low_value = temp.low_byte;
        temp.low_byte += value.low_byte;
        
        if(temp.low_byte == 0){
            temp.high_byte++;
        }else if(temp.low_byte < preview_low_value){
            temp.high_byte++;
        }
    }
    temp.high_byte += value.high_byte * multiplier;
    return temp;
}



double_long subtraction(double_long first_value, double_long second_value){ 
    if((first_value.high_byte > second_value.high_byte)|(first_value.high_byte >= second_value.high_byte)&(first_value.low_byte>=second_value.low_byte)){
        if(second_value.low_byte > first_value.low_byte)
            second_value.high_byte++;
        first_value.low_byte -= second_value.low_byte;
        first_value.high_byte -= second_value.high_byte;   
    }
    return first_value;
}


unsigned int division_64x(double_long first_value, double_long second_value){
    unsigned int result = 0;
    double_long tmp_second = second_value;
    if((second_value.high_byte == 0)&(second_value.low_byte == 0))
    {
        return -1;
    }
    if((first_value.high_byte == second_value.high_byte)\
            &(first_value.low_byte == second_value.low_byte))
        return result = 1;
    while((first_value.high_byte > second_value.high_byte)\
            |(first_value.high_byte >= second_value.high_byte)&(first_value.low_byte>=second_value.low_byte)){
        if(second_value.low_byte > first_value.low_byte)
        second_value.high_byte++;
        first_value.low_byte -= second_value.low_byte;
        first_value.high_byte -= second_value.high_byte;
        second_value.high_byte = tmp_second.high_byte;
        result++;
    }
    tmp_second = subtraction(tmp_second, first_value);
    if((first_value.high_byte >= tmp_second.high_byte)\
            &(first_value.low_byte>=tmp_second.low_byte))
        result++;
        
    return result;
}
