#ifndef my_SS1D_h
#define my_SS1D_h

#include <stdint.h>
#include <Arduino.h>

void SS1D_init(const uint8_t*);
void SS1D_clear(void);
void SS1D_write_int(const uint8_t);
void SS1D_write_char(const uint8_t);

#endif /* my_SS1D_h */
