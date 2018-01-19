/* 
 * File:   uart.h
 * Author: Kopranov_IN
 *
 * Created on 19 Декабрь 2017 г., 12:52
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <p24fj256da210.h>
#include <string.h>
    
#define SYSCLKU 40000000L
#define BAUDRATE 115200
#define BAUDRATEREG SYSCLKU/8/BAUDRATE-1
#define UART1_RX_TRIS TRISBbits.TRISB0
#define UART1_TX_TRIS TRISBbits.TRISB6

    
void UART1Init();
char UART1GetChar();
void UART1PutChar(char Ch);
void UART1PutStr(char* str);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

