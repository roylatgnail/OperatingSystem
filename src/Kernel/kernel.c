#include "./types.h"
#include "./gdt.h"

#include "./idt/idt.h"

#include "./drivers/vga.h"


void kernel(){
    gdt_GdtInit();  //We now have 4gb of memory to work with
    idt_InitIdt(); //Set up IDT for keyboard interrupts
    

    terminal_Init();
    terminal_WriteString("I like femboys\nand tomboys");
}