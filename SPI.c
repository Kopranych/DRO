
#include "SPI.h"

void spi_init()
{
    _SPI1IF = 0;//???? ?????????? ?? ?????????? ???????? ? SPI
    TRIS_SPI = 0;
    mapping_pin_spi();
    SPI1STATbits.SPIEN = 0;// enable SPI
    SPI1CON1 = 0;
    SPI1CON1bits.DISSCK = 0;// enable SCK as clock
    SPI1CON1bits.DISSDO = 0;//enable pin as SDO
    SPI1CON1bits.MODE16 = 1;//16 bit data
    SPI1CON1bits.MSTEN = 1;// master mode
    SPI1CON2bits.FRMEN = 0;
    SPI1CON2bits.SPIFSD = 0;
    SPI1CON2bits.SPIFPOL = 0;
    SPI1CON1bits.CKE = 1;//????????? ?????? ??? ???????? ?? ???????? ?????? ? ??????
    SPI1CON1bits.CKP = 1;// ?????????? ??????
    SPI1STATbits.SPIEN = 1;
}

unsigned int spi_txrx(unsigned int data)
{
    PORTFbits.RF5 = 0;
    unsigned int temp;
    SPI1BUF = data;
    while(_SPI1IF == 0);
    _SPI1IF = 0;
    temp = SPI1BUF;
    PORTFbits.RF5 = 1;
    return temp;
}

void spi_txrx_AD5312(unsigned int data)
{
    unsigned int prefix = 0x8000;
    spi_txrx(prefix|data<<2);
}


void mapping_pin_spi()
{
    __builtin_write_OSCCONL(OSCCON & 0xbf);//Unlock Registers use C30 built-in macro
    RPOR2bits.RP5R = 7;//assign output MOSI
    RPOR5bits.RP10R = 8;//assign output SCK
//   RPOR8bits.RP17R = 9;//assign output SS
    __builtin_write_OSCCONL(OSCCON | 0x40);//Lock Registers use C30 built-in macro
}


