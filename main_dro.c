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
#include "InterruptVector.h"
#include "calculation.h"

#define IDEAL_VALUE 512
#define MAX_VALUE 1023
#define MIN_VALUE 0

 int CONFIG4 __attribute__((space(prog), address(0x2ABF8))) = 0xFFFF ;
//_CONFIG4(

              
//);
 int CONFIG3 __attribute__((space(prog), address(0x2ABFA))) = 0xFCFF ;
//_CONFIG3(
//    WPFP_WPFP255 &       // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
//    SOSCSEL_EC &         // Secondary Oscillator Power Mode Select (External clock (SCLKI) or Digital I/O mode()
//    WUTSEL_LEG &         // Voltage Regulator Wake-up Time Select (Default regulator start-up time is used)
//    ALTPMP_ALPMPDIS &    // Alternate PMP Pin Mapping (EPMP pins are in default location mode)
//    WPDIS_WPDIS &        // Segment Write Protection Disable (Segmented code protection is disabled)
//    WPCFG_WPCFGDIS &     // Write Protect Configuration Page Select (Last page (at the top of program memory) and Flash Configuration Words are not write-protected)
//    WPEND_WPENDMEM       // Segment Write Protection End Page Select (Protected code segment upper boundary is at the last page of program memory; the lower boundary is the code page specified by WPFP)
//);
 int CONFIG2 __attribute__((space(prog), address(0x2ABFC))) = 0x1BDE ;//внешний такт
//_CONFIG2(
//    POSCMOD_HS &         // Primary Oscillator Select (HS Oscillator mode is selected)
//    IOL1WAY_ON &         // IOLOCK One-Way Set Enable (The IOLOCK bit (OSCCON<6>) can be set once, provided the unlock sequence has been completed. Once set, the Peripheral Pin Select registers cannot be written to a second time.)
//    OSCIOFNC_ON &        // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as port I/O (RC15))
//    FCKSM_CSDCMD &       // Clock Switching and Fail-Safe Clock Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
//    FNOSC_PRIPLL &       // Initial Oscillator Select (Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL))
//    PLL96MHZ_ON &        // 96MHz PLL Startup Select (96 MHz PLL is enabled automatically on start-up)
//    PLLDIV_DIV2 &        // 96 MHz PLL Prescaler Select (Oscillator input is divided by 2 (8 MHz input))
//    IESO_OFF             // Internal External Switchover (IESO mode (Two-Speed Start-up) is disabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x3D7F ;
//_CONFIG1(
//    WDTPS_PS32768 &      // Watchdog Timer Postscaler (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (Prescaler ratio of 1:128)
//    ALTVREF_ALTVREDIS &  // Alternate VREF location Enable (VREF is on a default pin (VREF+ on RA9 and VREF- on RA10))
//    WINDIS_OFF &         // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
//    FWDTEN_OFF &         // Watchdog Timer (Watchdog Timer is disabled)
//    ICS_PGx3 &           // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC3/PGED3)
//    GWRP_OFF &           // General Segment Write Protect (Writes to program memory are allowed)
//    GCP_OFF &            // General Segment Code Protect (Code protection is disabled)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG port is disabled)
//);

//#pragma config SOSCEL = IO
 

unsigned int DAC_current = IDEAL_VALUE;
unsigned long int freq_current;
unsigned long int freq_max, freq_min;

int main(int argc, char** argv) 
{ 
    unsigned int count = 0, flag = 0;//
    CLKDIVbits.CPDIV = 0b00;// postscaler PLL
    
    init_timer1();
//    init_timer23();
    init_timer45();
    spi_init();
    init_port_led();
    start_timer1_23_45();
    led_on(VD2);
    
    //измерение максимального и минимального значения частоты
    spi_txrx_AD5312(MAX_VALUE);
    while(count_timer < 2);//ждем актуального значения частоты
    freq_max = value_freqH<<16|value_freqL;
    spi_txrx_AD5312(MIN_VALUE);
    while(count_timer < 4);
    freq_min = value_freqH<<16|value_freqL;
    
    spi_txrx_AD5312(DAC_current);//так работают коменты или нет?
    flag_tmr1 = 0;
    
    while(1)
    {
 //       spi_txrx_AD5312(DAC_current);
        if(flag_tmr1)//
        {
            freq_current = value_freqH<<16|value_freqL;
            DAC_current = calcul_freq(freq_current, DAC_current);
            spi_txrx_AD5312(DAC_current);
            if(freq_current == PERFECT_FREQ)
                led_on(VD1);
            else led_off(VD1);
            flag_tmr1 = 0;
        }
 /*      led_on(LED_SYNH); 
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
        
     if(flag_interrupt)
       {
           invers_LED_SYNH();
           flag_interrupt = 0;
       }

 /*       if (_T1IF == 1)
        {
 /*           _T13F = 0;
            if (count == 1)
            {
 //               count = 0;
//                led_on(9);
                invers_LED_SYNH();
            }
            else if(count == 2)
            {
              led_off(9);
              count = 0;
 
            }
           invers_LED_SYNH();
              count++;
              TMR1 = 0;
              _T1IF = 0;
             
        }
 *///       spi_txrx_AD5312(500);
 //       led_on(10);
    }
    return (EXIT_SUCCESS);
}

void delay_ms(unsigned long int ms)
{
    unsigned long int i;
    for(i = 0; i < ms; i++);
 
}
