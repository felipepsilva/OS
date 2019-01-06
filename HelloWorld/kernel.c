//
// To build:
// 	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
// To link:
//	i686-elf-gcc -T link.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


#include <stddef.h>
#include <stdint.h>

void kernel_main()
{
	uint8_t* video_mem = (uint8_t*) 0xB8000;
	
	video_mem[0] = 'H';
	video_mem[2] = 'e';
	video_mem[4] = 'l';
	video_mem[6] = 'l';
	video_mem[8] = 'o';
	video_mem[10] = ' ';
	video_mem[12] = 'W';
	video_mem[14] = 'o';
	video_mem[16] = 'r';
	video_mem[18] = 'l';
	video_mem[20] = 'd';
	video_mem[22] = '!';
}