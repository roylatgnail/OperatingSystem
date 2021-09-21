#ifndef __GDT_H__
#define __GDT_H__

#include "./types.h"

struct gdt_GdtEntryStruct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed));

struct gdt_GdtPtrStruct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct gdt_GdtEntryStruct gdt_GdtEntryT;
typedef struct gdt_GdtPtrStruct gdt_GdtPtrT;

gdt_GdtEntryT gdt_GdtEntries[5];
gdt_GdtPtrT gdt_GdtPtr;

extern void gdt_GdtFlush(uint32_t);

static void gdt_GdtSetGate(int32_t num, uint32_t base, uint32_t limit, uint32_t access, uint8_t gran){
    gdt_GdtEntries[num].baseLow                 = (base & 0xFFFF);
    gdt_GdtEntries[num].baseMiddle              = (base >> 16) & 0xFF;
    gdt_GdtEntries[num].baseHigh                = (base >> 24) & 0xFF;

    gdt_GdtEntries[num].limitLow                = (limit & 0xFFFF);
    gdt_GdtEntries[num].granularity             = (limit >> 16) & 0x0F;

    gdt_GdtEntries[num].granularity             |= gran & 0xF0;
    gdt_GdtEntries[num].access                  = access;
}

static void gdt_GdtInit(){
    gdt_GdtPtr.limit = (sizeof(gdt_GdtEntryT) * 5) - 1;
    gdt_GdtPtr.base = (uint32_t)&gdt_GdtEntries;

    gdt_GdtSetGate(0, 0, 0, 0, 0);                  //Null segment
    gdt_GdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   //Code segment
    gdt_GdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   //Data segment
    gdt_GdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   //User mode code segment
    gdt_GdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   //User mode data segment

    //gdt_GdtFlush((uint32_t)&gdt_GdtPtr);
    gdt_GdtFlush((uint32_t)&gdt_GdtPtr);
}



#endif