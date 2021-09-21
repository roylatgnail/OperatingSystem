#ifndef __IDT_ISR_H__
#define __IDT_ISR_H__

#include "../types.h"
#include "../drivers/vga.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

typedef struct isr_IsrRegisters {
    //Data segment
    uint32_t ds;
    //Needed by pusha
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    //Error code + interrupt number
    uint32_t interruptNum;
    uint32_t errorCode;
    //Pushed by processor automatically
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
} isr_IsrRegistersT;

char *isr_ExceptionMessages[] = {
    "Division by zero",
    "Single step intterupt",
    "Non maskable interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Coprocessor not avaliable",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid task state segment",
    "Segment not present",
    "Stack segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "x87 floating point exception",
    "Alignment check",
    "Machine check",
    "Simple instruction multiple data floating point exception",
    "Virtualization exception",
    "Control protection exception"
};

void isr_IsrHandler(isr_IsrRegistersT reg){
    terminal_WriteString("Recieved interrupt: ");
    terminal_WriteString(isr_ExceptionMessages[reg.interruptNum]);
    terminal_WriteString("\n");
}

#endif