#ifndef __IDT_H__
#define __IDT_H__

#define low16(address) (uint16_t)((address) & 0xFFFF)
#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#include "../types.h"
#include "../ports.h"
#include "../std/string.h"

#include "./isr.h"

struct idt_IdtEntryStruct {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t baseHigh;
} __attribute__((packed));

struct idt_IdtPtrStruct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));



typedef struct idt_IdtEntryStruct idt_IdtEntryT;
typedef struct idt_IdtPtrStruct idt_IdtPtrT;

idt_IdtEntryT idt_IdtEntries[256];
idt_IdtPtrT idt_IdtPtr;


extern void idtFlush(uint32_t);

static void idt_IdtSetGate(uint8_t num, uint32_t handler){
    
    idt_IdtEntries[num].baseLow = low16(handler);
    idt_IdtEntries[num].selector = 0x08;
    idt_IdtEntries[num].always0 = 0;
    idt_IdtEntries[num].flags = 0x8E;
    idt_IdtEntries[num].baseHigh = high16(handler);
}

static void idt_InitIdt(){
    idt_IdtPtr.limit = sizeof(idt_IdtEntryT) * 256 - 1;
    idt_IdtPtr.base = (uint32_t)&idt_IdtEntries;
    memset(&idt_IdtEntries, 0, sizeof(idt_IdtEntryT)*256);
    
    idt_IdtSetGate(0, (uint32_t)isr0);
    idt_IdtSetGate(1, (uint32_t)isr1);
    idt_IdtSetGate(1, (uint32_t)isr2);
    idt_IdtSetGate(1, (uint32_t)isr3);
    idt_IdtSetGate(1, (uint32_t)isr4);
    idt_IdtSetGate(1, (uint32_t)isr5);
    idt_IdtSetGate(1, (uint32_t)isr6);
    idt_IdtSetGate(1, (uint32_t)isr7);
    idt_IdtSetGate(1, (uint32_t)isr8);
    idt_IdtSetGate(1, (uint32_t)isr9);
    idt_IdtSetGate(1, (uint32_t)isr10);
    idt_IdtSetGate(1, (uint32_t)isr11);
    idt_IdtSetGate(1, (uint32_t)isr12);
    idt_IdtSetGate(1, (uint32_t)isr13);
    idt_IdtSetGate(1, (uint32_t)isr14);
    idt_IdtSetGate(1, (uint32_t)isr15);
    idt_IdtSetGate(1, (uint32_t)isr16);
    idt_IdtSetGate(1, (uint32_t)isr17);
    idt_IdtSetGate(1, (uint32_t)isr18);
    idt_IdtSetGate(1, (uint32_t)isr19);
    idt_IdtSetGate(1, (uint32_t)isr20);
    idt_IdtSetGate(1, (uint32_t)isr21);
    idt_IdtSetGate(1, (uint32_t)isr22);
    idt_IdtSetGate(1, (uint32_t)isr23);
    idt_IdtSetGate(1, (uint32_t)isr24);
    idt_IdtSetGate(1, (uint32_t)isr25);
    idt_IdtSetGate(1, (uint32_t)isr26);
    idt_IdtSetGate(1, (uint32_t)isr27);
    idt_IdtSetGate(1, (uint32_t)isr28);
    idt_IdtSetGate(1, (uint32_t)isr29);
    idt_IdtSetGate(1, (uint32_t)isr30);
    idt_IdtSetGate(1, (uint32_t)isr31);
    
    idtFlush((uint32_t)&idt_IdtPtr);
}



#endif