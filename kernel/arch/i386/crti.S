BITS 32

section .init
global  _init
_init:
	push ebp
        mov esp, ebp
	; .init goes here

section .fini
global  _fini
_fini:
	push ebp
        mov esp, ebp
	; .fini goes here