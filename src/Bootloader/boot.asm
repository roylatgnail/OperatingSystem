MBALIGN  equ  1 << 0            
MEMINFO  equ  1 << 1           
FLAGS    equ  MBALIGN | MEMINFO 
MAGIC    equ  0x1BADB002       
CHECKSUM equ -(MAGIC + FLAGS)   
 

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text

[global gdt_GdtFlush]
gdt_GdtFlush:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush

.flush:
    ret

[GLOBAL idtFlush]
idtFlush:
    mov eax, [esp+4]
    lidt [eax]
    ret

%macro ISR_NOERRCODE 1          ;define a macro, taking one parameter
[GLOBAL isr%1]                  ;%1 accesses the first parameter.
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro 




[extern isr_IsrHandler]
isr_common_stub:
    pusha                       ;Push common registers

    mov ax, ds                  ;Push data segment registers
    push eax

    mov ax, 0x10                ;Kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp                    ;Hand stack to C function


    call isr_IsrHandler         ;Handle the idt_isr
    pop eax

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa

    add esp, 8
    iret

[GLOBAL idt_IdtFlush]
idt_IdtFlush:
    mov eax, [esp+4]
    lidt [eax]
    ret


global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	extern kernel
	call kernel
	cli
.hang:	hlt
	jmp .hang
.end: