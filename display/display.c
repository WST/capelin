
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//uint8_t xpos = 0;
//uint8_t ypos = 0;

//#define BIT_RS (1 << 2)
#define BIT_E (1 << 3)
//#define DATA_BITS(x) (( (x) & 0x0F ) << 4)

static inline void send_4bit(uint8_t bits, uint8_t rs)
{
	PORTD = ((bits & 0x0F) << 4) | BIT_E | ((rs & 0x01) << 2);
	_delay_us(5);
	PORTD &= ~BIT_E;
	_delay_us(5);
}

static inline void send_packet(uint8_t b, uint8_t rs)
{
	uint8_t hi = (b >> 4) & 0x0F;
	uint8_t low = b & 0x0F;

	send_4bit(hi, rs);
	send_4bit(low, rs);
}

static inline void LCDinit(uint8_t b)
{
	send_4bit(b, 0);
	_delay_us(40);
}

static inline void LCDcom(uint8_t b) {

	send_packet(b, 0);

	//PORTC = 0b00000010; //строб начала записи
	//PORTD = b; //команда
	//_delay_us(5); //поддержание высокого уровня строба начала записи
	//PORTC = 0x00; //окончание строба начала записи
}

void LCDdat(uint8_t b) {

	send_packet(b, 1);

	//PORTC = 0b00000011; //строб начала записи, вывод символа
	//PORTD = b; //символ
	//_delay_us(5); //поддержание высокого уровня строба начала записи
	//PORTC = 0x01; //окончание строба начала записи
}

void clear() {
	LCDcom(0b00000001);
	_delay_ms(2);
}

void putLine(const uint8_t *s) {
	for(int i = 0; i <= 15; i ++) {
		_delay_ms(1);
		LCDdat(s[i]);
	}
}

void enableCursor() {
	LCDcom(0x0F);
}

void disableCursor() {
	LCDcom(0b00001100);
}

void initDisplay() {
	_delay_ms(40);
	LCDinit(0b0011);
	LCDinit(0b0011);
	LCDinit(0b0011);
	LCDinit(0b0010);
	//LCDcom(0b00110000);
	//_delay_ms(5);
	//LCDcom(0b00110000);
	//_delay_us(120);
	//LCDcom(0b00110000);
	//_delay_ms(1);
	/*
	LCDcom(0b00101000); //выбор шины данных 4 бит, 2 строки
	//_delay_ms(5);
	LCDcom(0b00001000); //включение дисплея, курсор выключен, не мигает
	//_delay_ms(5);
	LCDcom(0b00000001); //очистка дисплея
	//_delay_ms(5);
	LCDcom(0b00000110); //сдвиг курсора вправо после вывода
	*/
	LCDcom(0b00101000);
	LCDcom(0b00000001);
	LCDcom(0b00000110);
	LCDcom(0b00001100);

}

int main(void) {

	// SETUP
	//DDRC = 0xFF; //порт C как выход
	DDRD = 0xFF; //порт D как выход
	PORTD = 0x00;

	//xpos = 0;
	//ypos = 0;

	initDisplay(); //инициализация дисплея

	enableCursor();
	

	//uint8_t *msg1 = ".Cirno Retro PC.";
	//uint8_t *msg2 = "(C) Ilya Averkov";
	//uint8_t *msg3 = "(C) Alex Zolotov";
	//uint8_t *msg4 = "ready           ";
	
	//putLine(msg1);
	//_delay_ms(1000);
	/*
	clear();
	putLine(msg2);
	_delay_ms(1000);
	clear();
	putLine(msg3);
	_delay_ms(1000);
	clear();
	putLine(msg4);
	_delay_ms(1000);
	//clear();
	*/
	
	// Основной цикл
	while(1) {
		//PORTD = PORTC;
	}
}
