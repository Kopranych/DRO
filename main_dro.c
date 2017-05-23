/* 
 * File:   main_dro.c
 * Author: Kopranov_IN
 *
 * Created on 17 ??? 2017 ?., 14:05
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256da210.h>
#include <p24Fxxxx.h>
#include "PIC24F_periph_features.h"
#include "led_dro.h"
/*
 * 
 */
void delay_ms(unsigned long int ms);

int main(int argc, char** argv) 
{
    spi_init();
    init_port_led();
    unsigned int count = 0, flag = 0;
    while(1)
    {
       led_on(LED_SYNH); 
       delay_ms(1000);
       led_off(LED_SYNH);
       led_on(LED_LOAD);
       delay_ms(1000);
       led_off(LED_LOAD);
       if(!flag)
       {
           if(count < 1023) count++;
           else flag = 1;
       } 
       else
       {
           if(count > 0) count--;
           else flag = 0;
       }
       spi_txrx_AD5312(count);

    }
    return (EXIT_SUCCESS);
}

void delay_ms(unsigned long int ms)
{
    unsigned long int i;
    for(i = 0; i < ms; i++);
 
}
