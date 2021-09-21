#ifndef __STRING_H__
#define __STRING_H__

#include "../types.h"

size_t strlen(const char* str){
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char *str1, const char *str2){
    const unsigned char *s1 = (const unsigned char *) str1;
    const unsigned char *s2 = (const unsigned char *) str2;
    unsigned char c1, c2;

    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;

        if (c1 == '\0') return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}


#endif