;
; To build:
; 	nasm -felf32 boot.asm -o boot.o
;

; Multiboot stuff

MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 1
FLAGS	 equ MBALIGN | MEMINFO
MAGIC	 equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)


section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
	
section .bss
align 16
stack_bottom:
	resb 16384	; 16KB stack, 16-byte aligned
stack_top: 		; the stack grows downwards


section .text
global _start:function (_start.end - _start) ; function symbol

; entry point
_start:

	; stack setup
	mov esp, stack_top
	
	; C code
	extern kernel_main
	call kernel_main
	
	
	; nothing more to do
	cli
.loop:
	hlt
	jmp .loop
.end: