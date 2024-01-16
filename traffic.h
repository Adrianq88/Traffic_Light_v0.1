/*
 * traffic.h
 *
 * Created: 20.06.2023 21:19:25
 *  Author: AP
 */


#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LED_PORT_1 PORTB
#define LED_DDR_1 DDRB
#define LED_PORT_2 PORTB
#define LED_DDR_2 DDRB

void GPIO_init();
void wykonaj_cykl(uint8_t, uint8_t);

#endif /* TRAFFIC_H_ */
