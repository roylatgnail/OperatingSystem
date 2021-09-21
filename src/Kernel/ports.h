#ifndef __PORTS_H__
#define __PORTS_H__

#include "./types.h"

void port_ByteOut(uint16_t port, uint8_t value){
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t port_ByteIn(uint16_t port){
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

uint16_t port_ByteWrite(uint16_t port){
    uint16_t ret;
    __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

#endif