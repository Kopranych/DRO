//Function timer



#include "Timer.h"



void init_timer1(void)
{
    /////// ???????????!!! ????????? ? CONFIG3 SOSCSEL_SOSC = External clock (SCLKI) or Digital I/) mode
    ////// ??? ????? TIMER1 ????? ???????? ?? ??????? ?????? ?????? ?? ?????? ??????? ?? 23???!!!!
    _T1IF = 0;//clear flag interrupt
    _T1IE = 1;//enable interrupt    
    _T1IP = 3;//set prioritet 4
    PORT_T1 = 0;
    TRIS_T1 = 0xFFFF;//port timer1 as input
    ANSCbits.ANSC14 = 0;//analog/digital pin
    PR1 = 1000;//period reset TMR1
    TMR1 = 0;//clear counter
    T1CONbits.TCS = 1;//source external clock
    T1CONbits.TCKPS = 0b11;//prescaler 1:1
    T1CONbits.TGATE = 0;//Gated Time Accumulation Enable bit
    T1CONbits.TSYNC = 1;//Do not synchronize external clock input
    T1CONbits.TSIDL = 0;//
    T1CONbits.TON = 0;//stop Timer1

}



void init_timer23(void)
{
    long Period = 4000000;
    long* pPeriod = &Period;
    PORTFbits.RF2 = 0;
    TRISFbits.TRISF2 = 1;//port timer2 as input
    mapping_pin_timer2RP0();//remap pin timer2 to RP0
    
//    PR2 = 0;//
//    PR3 = 0;
    T2CON = 0x0000; //Stops any 16/32-bit Timer2 operation
    T3CON = 0;//no use
    PR2 = 50000;
    PR3 = *pPeriod;
   
    T2CONbits.TON = 0;
    T2CONbits.TCS = 1;//
    T2CONbits.TCKPS1 = 0;//prescaler 
    T2CONbits.TCKPS0 = 0;//1:256
    T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    TMR2 = 0;//clear counter T2
    TMR3 = 0;//clear counter T3
    _T2IE = 0;//disable interrupt timer2
    _T2IF = 0; 
    _T2IP = 4;
    _T3IF = 0;//clear flag interrupt
    _T3IE = 0;//enable interrupt    
    _T3IP = 4;//set prioritet 4
}

void init_timer45(void)
{
    long Period = 4000000;
    long* pPeriod = &Period;
    PORTFbits.RF2 = 0;
    TRISFbits.TRISF2 = 1;//port timer2 as input
    mapping_pin_timer4RP0();//remap pin timer2 to RP0
    
//    PR2 = 0;//
//    PR3 = 0;
    T4CON = 0x0000; //Stops any 16/32-bit Timer2 operation
    T5CON = 0x0000;//no use
    TMR4 = 0;//clear counter T2
    TMR5 = 0;//clear counter T3
    PR4 = 0xFFFF;
    PR5 = 0xFFFF;  
    _T4IE = 0;//disable interrupt timer2
    _T4IF = 0; 
    _T4IP = 4;
    _T5IF = 0;//clear flag interrupt
    _T5IE = 0;//enable interrupt    
    _T5IP = 4;//set prioritet 4
    T4CONbits.TON = 0;
    T4CONbits.TCS = 1;//
    T4CONbits.TCKPS1 = 0;//prescaler 
    T4CONbits.TCKPS0 = 0;//1:256
    T4CONbits.TGATE = 0;
    T4CONbits.TSIDL = 0;
    T4CONbits.T45 = 1;   
}

void start_timer1_23_45(void)
{
    T1CONbits.TON = 1;//
    T2CONbits.TON = 1;
    T4CONbits.TON = 1;
}



void mapping_pin_timer2RP0(void)
{
    __builtin_write_OSCCONL(OSCCON & 0xbf);//Unlock Registers use C30 built-in macro
    RPINR3 = 0x1E;//Assign T2 To Pin RP30
//    RPINR4 = 0x25;//Assign T4 To Pin RPi37
    RPOR2bits.RP5R = 7;//assign output MOSI
    RPOR5bits.RP10R = 8;//assign output SCK
//    RPOR9bits.RP19R = 9;//assign output SS
/*    RPINR3bits.T2CKR0 = 1;//Assign T2 To Pin RP0
    RPINR3bits.T2CKR1 = 0;
    RPINR3bits.T2CKR2 = 0;
    RPINR3bits.T2CKR3 = 0;
    RPINR3bits.T2CKR4 = 0;
    RPINR3bits.T2CKR5 = 0;
*/  __builtin_write_OSCCONL(OSCCON | 0x40);//Lock Registers use C30 built-in macro
}

void mapping_pin_timer4RP0(void)
{
    __builtin_write_OSCCONL(OSCCON & 0xbf);//Unlock Registers use C30 built-in macro
    RPINR4bits.T4CKR = 0x1E;//Assign T2 To Pin RP30

    RPOR2bits.RP5R = 7;//assign output MOSI
    RPOR5bits.RP10R = 8;//assign output SCK
    __builtin_write_OSCCONL(OSCCON | 0x40);//Lock Registers use C30 built-in macro
}

/*задержка в 1 секунду с поиощью таймера
#define SYSCLK 8000000
#define t1 1
#define PREG SYSCLK/2*t1/256
*/
