CFLAGS=-Wall -ffunction-sections -mcall-prologues -mmcu=atmega328 -Os
LDFLAGS=-Wl,-gc-sections -Wl,-relax
CC=avr-gcc
OBJECT_FILES=mem.o

all: blink.h mem.hex

blink2: blink2.h mem.hex

clean:
	rm -f *.o *.hex *.obj blink.bin blink.h

mem.hex: mem.obj
	avr-objcopy -R .eeprom -O ihex $< $@

%.obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

blink.h:
	z80asm -o blink.bin blink.z80
	xxd -i blink.bin > blink.h

blink2.h:
	z80asm -o blink.bin blink2.z80
	xxd -i blink.bin > blink.h
