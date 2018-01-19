#include "uart.h"



void UART1Init()
{
    ANSBbits.ANSB0 = 0;
    ANSBbits.ANSB6 = 0;
    UART1_TX_TRIS = 0;
    UART1_RX_TRIS = 1;
    U1BRG = BAUDRATEREG;// скорость обмена данными
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1MODEbits.UARTEN = 1;// разрешение работы модуля 
    U1STA = 0;
    U1STAbits.UTXEN = 1;// разрешение передачи 
    IFS0bits.U1RXIF = 0;// сброс флага прерывания
}    



char UART1GetChar()
{
    char Temp;
    while(IFS0bits.U1RXIF == 0);
    Temp = U1RXREG;
    IFS0bits.U1RXIF = 0;
    return Temp;
}

void UART1PutChar(char Ch)
{
    while(U1STAbits.UTXBF == 1);
    U1TXREG = Ch;
}


void UART1PutStr(char str[]){
    int size = strlen(str);
    int i;
    for(i = 0; i < size;i++){
        UART1PutChar(str[i]);
    }
    UART1PutChar(0xD);
    UART1PutChar(0xA);
}


