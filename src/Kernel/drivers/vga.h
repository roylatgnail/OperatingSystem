#ifndef __VGA_H__
#define __VGA_H__

#include "../std/string.h"

#define VIDEO_ADDRESS 0xb8000
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIG 0x0e
#define MAX_ROWS 25
#define MAX_COLS 80

size_t terminalRow;
size_t terminalCol;
uint8_t terminalColor;
uint16_t *terminalBuffer;

enum VgaColor {
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE
};

static inline uint8_t vgaEntryColor(enum VgaColor fg, enum VgaColor bg){ return fg | bg << 4; }
static inline uint16_t vgaEntry(unsigned char uc, uint8_t color){ return (uint16_t) uc | (uint16_t) color << 8; }

void terminal_SetColor(uint8_t color){ terminalColor = color; }

void terminal_PutEntryAt(char c, uint8_t color, size_t x, size_t y){
    const size_t index= y * MAX_COLS + x;
    terminalBuffer[index] = vgaEntry(c, color);
}

void terminal_PutChar(char c){
    if (c == '\n'){
        ++terminalRow;
        terminalCol = 0;
    }

    else {
        terminal_PutEntryAt(c, terminalColor, terminalCol, terminalRow);

        if (++terminalCol == MAX_COLS){
            terminalCol = 0;
            if (++terminalRow == MAX_ROWS) terminalRow = 0;



        }
    }
}

void terminal_Write(const char* data, size_t size){
    for (size_t i=0; i < size; i++)
        terminal_PutChar(data[i]);
}

void terminal_WriteString(const char *data){
    terminal_Write(data, strlen(data));
}

void terminal_Clear(){
    for (size_t y=0; y < MAX_ROWS; y++){
        for (size_t x=0; x < MAX_COLS; x++){
            const size_t index = y * MAX_COLS + x;
            terminalBuffer[index] = vgaEntry(' ', terminalColor);
        }
    }

}

void terminal_Init(){
    terminal_Clear();

    terminalRow = 0;
    terminalCol = 0;
    terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminalBuffer = (uint16_t*) 0xB8000;
}


#endif