#ifndef __IO_H_
#define __IO_H_

#include "reg.h"

void usart_init(void);
void print_str(const char *str);
char get_byte(void);
#endif

