
all: kernel boot link

clean:
	rm *.o
	rm *.bin

kernel:
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	
boot:
	nasm -felf32 boot.asm -o boot.o

link:
	i686-elf-gcc -T link.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc