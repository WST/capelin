
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define PIN_OE 0b00000001

#include "blink.h"

/**
 * Если на пине B0 у нас ноль, следовательно, идёт обращение к памяти
 * Порт Д ставим как выход
 * В противном случае — как вход
 */
static inline uint8_t getPortDMask() {
	return ( (PINB & PIN_OE) == 0x00) ? 0xFF : 0x00;
}

int main(void) {
	DDRB = 0x00; // порт B — вход (B0 = !MREQ)
	DDRC = 0x00; // Порт C — адресная шина
	DDRD = 0xFF; // Порт D — шина данных — выход когда mreq=0

	// Бесконечный цикл
	while(1) {
		uint8_t mask = getPortDMask();
		DDRD = mask;
		if(mask == 0xFF) {
			uint8_t address = PINC % blink_bin_len;
			PORTD = blink_bin[address];
		}
	}
}
