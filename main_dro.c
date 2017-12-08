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
//#include "led_dro.h"
#include "InterruptVector.h"
#include "calculation.h"


#define IDEAL_VALUE 512
#define MAX_VALUE 1023
#define MIN_VALUE 0
#define LIMIT_FREQ_MEAS 0x989680

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
//float freq_current, freq_avarege = 0;
unsigned long int freq_max; //4200001735L, 
unsigned long int freq_min;//4199997914L;
//unsigned long freq_current;
unsigned long freq_avarege[] = {1,1,1,1,1,1,1,1,1,1};
unsigned long freq_test = 5;
unsigned int count_meas = 0, flag = 0;//
unsigned long int freqL = 0, freqH = 0;
fifo_t buf_fifo;
int is_full = 1, is_first = 1;
double_long point;
double_long freq_current;
double_long perfect_freq;
unsigned long perfect_range_freq = 500;
int count = 20;
        
//массив опорных значений частоты
unsigned long buf_ref_freq_high[MAX] = {0,0,0,0,0};
unsigned long buf_ref_freq_low[MAX] = {0x5F5E100,0xBEBC200,0x11E1A300,0x17D78400,0x1DCD6500};
double_long buf_ref_freq[MAX];
//массив значений диапазона отклонений частоты
unsigned long array_range_freq[MAX] = {100,200,300,400,500};

//опорные значени€ частоты дл€ сравнени€ с измеренными значени€ми
typedef enum{  
    ref1,
    ref2,
    ref3,
    ref4,
    ref5
}perfect;

perfect reference_freq;

// режимы работы устройства: режим вхождение в синхронизм; 
//режим синхронизма
typedef enum{  
    Mode_entering_synchronysm,
    Mode_synchronysm
}Mode;

Mode device;

/* 
* вывод значени€ измеренного значени€ частоты на светодиоды
* если измеренна€ больше эталонной горит VD1
* если меньше горит VD2
* если равны гор€т оба светодиода
*/
void display_freq_current(double_long freq, double_long buf_ref_freq);

//инициализаци€ и первоначальное заполнение буфера фифо
void first_filling_fifo(fifo_t *fifo);

// при отладеке проверить значени€ буфера фифо
void test_fifo(fifo_t fifo_test);

/*
 * »нициализаци€ переферии контроллера: таймеры, spi, выводы диодов
 */
void init_controller(void);
//измерение максимального и минимального значени€ частоты
void measur_max_min_value_freq(void);

//задержка в секундах примерна€
void _delay_s(unsigned long s);

//инициализаци€ буфера
double_long* init_buf_ref(double_long* buf_ref_freq,\
        unsigned long* buf_ref_freq_high, unsigned long* buf_ref_freq_low); 

double_long init_value_perfect_freq(unsigned long high_byte, unsigned long low_byte);


int main(int argc, char** argv) 
{ 
    unsigned int first = 5;
    unsigned int second = 6;
    unsigned int result = first - second;
    //инициализаци€ переферии и настройка контроллера
    init_controller();
    start_timer1_23_45();
    init_buf_ref(buf_ref_freq, buf_ref_freq_high, buf_ref_freq_low);
    //измерение максимального и минимального значени€ частоты
//    measur_max_min_value_freq();
    double_long first_value = init_value_perfect_freq(0x17, 0x4876E800);
    double_long second_value = init_value_perfect_freq(0x00, 0xF46B0400);
//    perfect_freq = init_value_perfect_freq(0x00, 0x00);
//    perfect_freq = subtraction(first_value, second_value);
//    spi_txrx_AD5312(DAC_current);//
    
    
//    заполн€ем первыми значени€ми буфер фифо
    init_fifo(&buf_fifo);
    
    result = division_64x(first_value, second_value);
    flag_tmr1 = 0;
    unsigned long i;
    for(i = 0; i < 1000000; i+=100000){
        perfect_freq = init_value_perfect_freq(0x00 , 0x4876E800 + i);
        perfect_freq = multiplication_x64(perfect_freq, 16383);
        result = division_64x(perfect_freq, first_value);
        fifo_put(&buf_fifo, result, result);
    }
    flag_tmr1 = 0;
   
    while(count_meas < MAX)
    {
        if(flag_tmr1)
        {
            if(is_first)
            {
                is_first = 0;
                flag_tmr1 = 0;
                clear_counter_all_timer();
                count_timer = 0;
            }
            else
            {
                is_full = fifo_put(&buf_fifo, high_bitnes_tmr45, value_freqH<<16|value_freqL);
                freq_current.high_byte = high_bitnes_tmr45;
                freq_current.low_byte = value_freqH<<16|value_freqL;
                count_meas++;
                flag_tmr1 = 0;
                display_freq_current(freq_current, buf_ref_freq[reference_freq]);
                DAC_current = calcul_freq(freq_current, DAC_current,\
                        buf_ref_freq[reference_freq],  array_range_freq[reference_freq],count);// вычисл€ем разность между эталоном и измеренным значением
                spi_txrx_AD5312(DAC_current);//корректируем значение ÷јѕ на величину разности
                reference_freq++;
            }
        }
    }
//    flag_tmr1 = 0;
//    freq_current = value_freqH<<16|value_freqL;
//  //            summa_array(&buf_fifo);
//    DAC_current = calcul_freq(freq_current, DAC_current);
//    spi_txrx_AD5312(DAC_current);
    
    
    
 //сделать задержку 10 сек дл€ стабилизации генератора после поправки цапом   
    while(1)
    {   
        if(flag_tmr1){
            
                point = fifo_get(&buf_fifo);
                freq_current.high_byte -= point.high_byte;//выкидываем первое значение в буфере  
                freq_current.low_byte -= point.low_byte;
                fifo_put(&buf_fifo, high_bitnes_tmr45, value_freqH<<16|value_freqL);//кладем новое значение в конец буфера  
                freq_current.high_byte += high_bitnes_tmr45;
                freq_current.low_byte += value_freqH<<16|value_freqL;//
                flag_tmr1 = 0;  
 //               display_freq_current(freq_current, perfect_freq);
                DAC_current = calcul_freq(freq_current, DAC_current,
                        perfect_freq,  perfect_range_freq,count--);// вычисл€ем разность между эталоном и измеренным значением
                spi_txrx_AD5312(DAC_current);//корректируем значение ÷јѕ на величину разности 
            }
    }  
    return (EXIT_SUCCESS);
}

void _delay_s(unsigned long s){
    s = s*3200000;
    unsigned long int i;
    for(i = 0; i < s; i++);
}


void display_freq_current(double_long freq, double_long buf_ref_freq){
      if((freq.high_byte == buf_ref_freq.high_byte)&\
              (freq.low_byte == buf_ref_freq.low_byte))
            {
                led_on(VD1);
                led_on(VD2);
            }
            else 
                if((freq.high_byte >= buf_ref_freq.high_byte)&\
              (freq.low_byte > buf_ref_freq.low_byte))
                {
                    led_on(VD1);
                    led_off(VD2);
                }
            else 
                if((freq.high_byte <= buf_ref_freq.high_byte)&\
              (freq.low_byte < buf_ref_freq.low_byte))
                {
                    led_on(VD2);
                    led_off(VD1);
                }
                else {
                    led_off(VD1);
                    led_off(VD2);
                }
}

//void first_filling_fifo(fifo_t *fifo){
//    
//    init_fifo(fifo);
//    
//    while(is_full)
//    {
//        if(flag_tmr1)
//        {
//            if(is_first)
//            {
//                fifo_get(fifo);
//                is_first = 0;
//                flag_tmr1 = 0;
//                clear_counter_all_timer();
//            }
//            else
//            {
//                is_full = fifo_put(fifo, value_freqH<<16|value_freqL);
//                count_meas++;
//                flag_tmr1 = 0;
//            }
//        }
//    }
//}

//void test_fifo(fifo_t fifo_test){
//    //Test fifo    
//    init_fifo(&fifo_test);
//    for(is_full = 0; is_full<10;is_full++)
//    {
//        if(is_full <4){
//            fifo_put(&fifo_test, is_full);
//        }
//        else if(is_full>=4&is_full< 7)
//        {
//            fifo_get(&fifo_test);
//        }
//        else if(is_full>=7)
//        {
//            fifo_put(&fifo_test, is_full);
//        }    
//    }
//}



void init_controller(void){
    CLKDIVbits.CPDIV = 0b00;// postscaler PLL

    init_timer1();
    init_timer23();
    init_timer45();
    spi_init();
    init_port_led();
}


void measur_max_min_value_freq(void){
    spi_txrx_AD5312(MIN_VALUE);
    while(count_timer < 2);
    freq_min = value_freqH<<16|value_freqL;
    spi_txrx_AD5312(MAX_VALUE);
    while(count_timer < 4);//ждем актуального значени€ частоты
    freq_max = value_freqH<<16|value_freqL;
    spi_txrx_AD5312(512);
    while(count_timer < 5);
}

double_long* init_buf_ref(double_long buf_ref_freq[],\
        unsigned long buf_ref_freq_high[], unsigned long buf_ref_freq_low[]){
    int i;
    for(i=0; i < MAX;i++)
    {
        buf_ref_freq[i].high_byte = buf_ref_freq_high[i];
        buf_ref_freq[i].low_byte = buf_ref_freq_low[i];
    }
    return buf_ref_freq;
}

double_long init_value_perfect_freq(unsigned long high_byte, unsigned long low_byte){
    double_long perfect_freq;
    perfect_freq.high_byte = high_byte;
    perfect_freq.low_byte = low_byte;
    return perfect_freq;
}
