#ifndef my_SS1D_h
#define my_SS1D_h

#include <stdint.h>
#include <Arduino.h>

void SS1D_init(uint8_t*);
void SS1D_clear(void);
void SS1D_write_int(uint8_t);
void SS1D_write_char(uint8_t);

#endif /* my_SS1D_h */
