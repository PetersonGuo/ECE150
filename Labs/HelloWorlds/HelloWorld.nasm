;~.~. Definitions for readability: ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.
	%define  SYS_EXIT   1
	%define  SYS_READ   3
	%define  SYS_WRITE  4
	%define  STDIN      0
	%define  STDOUT     1
	%define  STDERR     2

section .text
	global _start

_start:
	mov cx, 5
	call _print
_print:
	mov ecx, msg
	mov edx, msg.len
	mov eax, SYS_WRITE
	mov ebx, STDOUT
	int 80h

	dec cx
	cmp cx, 0
	jne _print
	
	xor ebx, ebx
	mov eax, SYS_EXIT
	int 80h

section .data
	msg: db "Hello, World!", 10
	msg.len: equ $ - msg
