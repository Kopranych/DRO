/* 
 * File:   led_dro.h
 * Author: Kopranov_IN
 *
 * Created on 17 ??? 2017 ?., 14:08
 */

#ifndef LED_DRO_H
#define	LED_DRO_H

#ifdef	__cplusplus
extern "C" {
#endif

 #include <p24fj256da210.h>



#define PORT_LED PORTA
#define TRIS_LED TRISA
#define RA0 0
#define LED_SYNH PORTAbits.RA9
#define LED_LOAD PORTAbits.RA10

void init_port_led(void);
void invers_LED_LOAD(void);
void invers_LED_SYNH(void);
void led_off(unsigned int pin);
void led_on(unsigned int pin);
  

#ifdef	__cplusplus
}
#endif

#endif	/* LED_DRO_H */

