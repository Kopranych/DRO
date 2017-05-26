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

 int CONFIG4 __attribute__((space(prog), address(0x2ABF8))) = 0xFFFF ;
//_CONFIG4(

              
//);
 int CONFIG3 __attribute__((space(prog), address(0x2ABFA))) = 0xFFFF ;
//_CONFIG3(
//    WPFP_WPFP255 &       // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
//    SOSCSEL_SOSC &       // Secondary Oscillator Power Mode Select (Secondary oscillator is in Default (high drive strength) Oscillator mode)
//    WUTSEL_LEG &         // Voltage Regulator Wake-up Time Select (Default regulator start-up time is used)
//    ALTPMP_ALPMPDIS &    // Alternate PMP Pin Mapping (EPMP pins are in default location mode)
//    WPDIS_WPDIS &        // Segment Write Protection Disable (Segmented code protection is disabled)
//    WPCFG_WPCFGDIS &     // Write Protect Configuration Page Select (Last page (at the top of program memory) and Flash Configuration Words are not write-protected)
//    WPEND_WPENDMEM       // Segment Write Protection End Page Select (Protected code segment upper boundary is at the last page of program memory; the lower boundary is the code page specified by WPFP)
//);
 int CONFIG2 __attribute__((space(prog), address(0x2ABFC))) = 0xFAFF ;
//_CONFIG2(
//    POSCMOD_NONE &       // Primary Oscillator Select (Primary oscillator is disabled)
//    IOL1WAY_ON &         // IOLOCK One-Way Set Enable (The IOLOCK bit (OSCCON<6>) can be set once, provided the unlock sequence has been completed. Once set, the Peripheral Pin Select registers cannot be written to a second time.)
//    OSCIOFNC_OFF &       // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
//    FCKSM_CSDCMD &       // Clock Switching and Fail-Safe Clock Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
//    FNOSC_PRI &          // Initial Oscillator Select (Primary Oscillator (XT, HS, EC))
//    PLL96MHZ_ON &        // 96MHz PLL Startup Select (96 MHz PLL is enabled automatically on start-up)
//    PLLDIV_DIV12 &       // 96 MHz PLL Prescaler Select (Oscillator input is divided by 12 (48 MHz input))
//    IESO_ON              // Internal External Switchover (IESO mode (Two-Speed Start-up) is enabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x3DFF ;
//_CONFIG1(
//    WDTPS_PS32768 &      // Watchdog Timer Postscaler (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (Prescaler ratio of 1:128)
//    ALTVREF_ALTVREDIS &  // Alternate VREF location Enable (VREF is on a default pin (VREF+ on RA9 and VREF- on RA10))
//    WINDIS_OFF &         // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
//    FWDTEN_ON &          // Watchdog Timer (Watchdog Timer is enabled)
//    ICS_PGx3 &           // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC3/PGED3)
//    GWRP_OFF &           // General Segment Write Protect (Writes to program memory are allowed)
//    GCP_OFF &            // General Segment Code Protect (Code protection is disabled)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG port is disabled)
//);


void delay_ms(unsigned long int ms);

int main(int argc, char** argv) 
{ 
    init_timer1();
    spi_init();
    init_port_led();
    unsigned int count = 0, flag = 0;
    start_timer1_23();
    led_on(10);
    while(1)
    {
  /*     led_on(LED_SYNH); 
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
*/
        if (_T1IF == 1)
        {
 //           _T1IF = 0;
            if (count == 2)
            {
 //               count = 0;
                led_on(9);
 //               invers_LED_SYNH();
            }
            else if(count == 4)
            {
              led_off(9);
              count = 0;
 
            }
              count++;
              TMR1 = 0;
              _T1IF = 0;
        }

    }
    return (EXIT_SUCCESS);
}

void delay_ms(unsigned long int ms)
{
    unsigned long int i;
    for(i = 0; i < ms; i++);
 
}
