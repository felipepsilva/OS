#include <stddef.h>
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %0, %1"
		:
	: "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
		: "=a"(ret)
		: "Nd"(port));
	return ret;
}

int is_transmit_empty() {
	return inb(0x3f8 + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);

	outb(0x3f8, a);
}

void kernel_main()
{
	outb(0x3f8 + 1, 0x00); // clear interrupts

	outb(0x3f8 + 3, 0x80); // MSB on line control register
	outb(0x3f8 + 0, 0x03); // divisor lo (3 for 38400 baud (115200 / 3 = 38400))
	outb(0x3f8 + 1, 0x00); // divisor hi

	outb(0x3f8 + 3, 0x03); // 0000 0011 - 8 bits characte, 1 stop bit, no parity set
						   //   || ||||
						   //   || |||+-> Data Bit   number of bits in a character
						   //   || ||+--> Data Bit   (00=5, 01=6, 10=7, 11=8)
						   //   || ||
						   //   || |+---> Stop Bit   0 = 1 stop bit, 1 = depends on char len
						   //   || |
						   //   || +----> Parity bit
						   //   |+------> Parity bit
						   //   +-------> Parity bit

	outb(0x3f8 + 2, 0xC7); // FCR  1100 0111
						   //      |||| ||||
						   //      |||| |||+-> Enable FIFO
						   //      |||| ||+--> Clear receive FIFO
						   //      |||| |+---> Clear transmit FIFO
						   //      |||| +----> DMA mode select
						   //      |||+------> Reserved
						   //      ||+-------> Enable 64 byte FIFO
						   //      |+--------> Trigger level | 00 = 1 byte    01 = 4 bytes
						   //      +---------> Trigger level | 10 = 8 bytes   11 = 14 bytes

	outb(0x3f8 + 4, 0x0B); // 0000 1101
						   // |||| ||||
						   // |||| |||+-> Force Data Terminal Ready
						   // |||| ||+--> Force Request to Send
						   // |||| |+---> Aux Output 1
						   // |||| +----> Aux Output 2 (interrupt enable)
						   // |||+------> Loopback mode
						   // ||+-------> Autoflow
						   // |+--------> Reserved
						   // +---------> Reserved

	write_serial('H');
	write_serial('e');
	write_serial('L');
	write_serial('l');
	write_serial('O');
	write_serial(',');
	write_serial('S');
	write_serial('E');
	write_serial('r');
	write_serial('I');
	write_serial('a');
	write_serial('L');
	write_serial('!');
}
