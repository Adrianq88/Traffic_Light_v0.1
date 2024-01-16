/*
 * traffic_functions.c
 *
 * Created: 14.06.2023 21:19:09
 *  Author: AP
 */ 
#include "traffic.h"

// STEROWNIK WYŒWIETLACZA 7-SEGMENTOWEGO
const uint8_t prime[] PROGMEM = {
	0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B // od 0 do 9
	//0x7B, 0x7F, 0x70, 0x5F, 0x5B, 0x33, 0x79, 0x6D, 0x30, 0x7E // od 9 do 0
};

void GPIO_init() {	// inicjalizacja wykorzystywanych portów
	DDRC = 0xFF; // piny portu C na wyjœcie
	DDRD = 0xFF; // piny portu D na wyjœcie
	LED_DDR_1 |= (1 << PB0) | (1 << PB1) | (1 << PB2);  // ustawienie pinów PB0, PB1 i PB2 dla pierwszego sygnalizatora jako wyjœcia
	LED_DDR_2 |= (1 << PB3) | (1 << PB4) | (1 << PB5);  // ustawienie pinów PB3, PB4 i PB5 dla drugiego sygnalizatora jako wyjœcia
}

void display_select(uint8_t display) {
	switch (display) {
		case 0:
			PORTC = ~(1 << PC0);
			break;
		case 1:
			PORTC = ~(1 << PC1);
			break;
		case 2:
			PORTC = ~(1 << PC2);
			break;
		case 3:
			PORTC = ~(1 << PC3);
			break;
	}
}

void wykonaj_cykl(uint8_t opoznienie, uint8_t start) {
	uint8_t start_number = 99-start; // liczba pocz¹tkowa
	uint8_t end_number = 99; // liczba koñcowa
	LED_PORT_1 |= (1 << PB0);	//czerwony (1) = ON
	LED_PORT_2 |= (1 << PB5);	//zielony (2) = ON
		
	uint8_t current_number = start_number;
	for (uint8_t i = current_number / 10; i <= end_number / 10; i++) {
		uint8_t j_start = (i == current_number / 10) ? (current_number % 10) : 0;
        uint8_t j_end = (i == end_number / 10) ? (end_number % 10) : 9;
		for (uint8_t j = j_start; j <= j_end; j++) {
			for (uint8_t k = 0; k <= opoznienie; k++) {
				display_select(3); // dziesi¹tki
				PORTD = ~pgm_read_byte(&prime[9-i]);
				_delay_ms(25);
				display_select(2); // jednoœci
				PORTD = ~pgm_read_byte(&prime[9-j]); 
				_delay_ms(25);
				// wyœwietla "--", gdy zielone
				display_select(1); // dziesi¹tki
				PORTD = ~0x01;
				_delay_ms(25);
				display_select(0); // jednoœci
				PORTD = ~0x01; 
				_delay_ms(25);
			}
		}
	}
	//z czerwonego na zielone (1) i z zielonego na czerwone (2)
	LED_PORT_1 |= (1 << PB1);	//¿ó³ty (1) = ON
	LED_PORT_2 &= ~(1 << PB5);	//zielony (2) = OFF
	LED_PORT_2 |= (1 << PB4);	//¿ó³ty (2) = ON
	_delay_ms(20000);

	LED_PORT_1 &= ~(1 << PB0);  //czerwony (1) = OFF
	LED_PORT_1 &= ~(1 << PB1);  //¿ó³ty (1) = OFF
	LED_PORT_2 &= ~(1 << PB4);  //¿ó³ty (2) = OFF
	_delay_ms(500);


	LED_PORT_1 |= (1 << PB2);	//zielony (1) = ON
	LED_PORT_2 |= (1 << PB3);	//czerwony (2) = ON
		
	current_number = start_number;
    for (uint8_t i = current_number / 10; i <= end_number / 10; i++) {
		uint8_t j_start = (i == current_number / 10) ? (current_number % 10) : 0;
        uint8_t j_end = (i == end_number / 10) ? (end_number % 10) : 9;
		for (uint8_t j = j_start; j <= j_end; j++) {
			for (uint8_t k = 0; k <= opoznienie; k++) {
				display_select(1); // dziesi¹tki
				PORTD = ~pgm_read_byte(&prime[9-i]);
				_delay_ms(25);
				display_select(0); // jednoœci
				PORTD = ~pgm_read_byte(&prime[9-j]); 
				_delay_ms(25);
				// wyœwietla "--", gdy zielone
				display_select(3); // dziesi¹tki
				PORTD = ~0x01;
				_delay_ms(25);
				display_select(2); // jednoœci
				PORTD = ~0x01; 
				_delay_ms(25);
			}
		}
	}
	//z zielonego na czerwone (1) i z czerwonego na zielone (2)
	LED_PORT_1 &= ~(1 << PB2);	//zielony (1) = OFF
	LED_PORT_1 |= (1 << PB1);	//¿ó³ty (1) = ON
	LED_PORT_2 |= (1 << PB4);	//¿ó³ty (2) = ON
	_delay_ms(20000);

	LED_PORT_1 &= ~(1 << PB1);  //¿ó³ty (1) = OFF
	LED_PORT_2 &= ~(1 << PB3);	//czerwony (2) = OFF
	LED_PORT_2 &= ~(1 << PB4);	//¿ó³ty (2) = OFF
	_delay_ms(500);
}