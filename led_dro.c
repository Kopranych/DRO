
#include "led_dro.h"

void init_port_led(void)
{
    TRIS_LED &= ~((1<<RA0)|(1<<9)|(1<<10));
    PORT_LED &= ~((1<<RA0)|(1<<9)|(1<<10)); 
    ANSA = 0;//I/0 digital output
}

void led_off(unsigned int pin)
{
     PORT_LED &= ~(1<<pin);
}

void led_on(unsigned int pin)
{
    PORT_LED |= 1<<pin;
}

void invers_LED_LOAD(void)
{
    LED_LOAD = ~LED_LOAD;
}

void invers_LED_SYNH(void)
{
    LED_SYNH = ~LED_SYNH;
}



