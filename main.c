/* PROJEKT STEROWNIKA SYGNALIZACJI �WIETLNEJ

Autor
Adrian Pr�dki
*/
#include "traffic.h"
#define F_CPU 800000UL

int main(void) {
	GPIO_init();
	while(1) {
		wykonaj_cykl(100,20); //(op�nienie; od)
	}
}