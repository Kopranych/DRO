#include "led_dro.h"

void init_port_led(void)
{
    TRIS_LED &= ~((1<<RA0)|(1<<LED_SYNH)|(1<<LED_LOAD));
    PORT_LED &= ~((1<<RA0)|(1<<LED_SYNH)|(1<<LED_LOAD));   
}

void led_off(unsigned int pin)
{
     PORT_LED &= ~(1<<pin);
}

void led_on(unsigned int pin)
{
    PORT_LED |= 1<<pin;
}

void invers_led1()
{
    PORT_LED ^= 1<<RA0;
}

void invers_led2()
{
    PORT_LED ^= 1<<RA0;
}



