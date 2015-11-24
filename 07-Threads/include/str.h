#ifndef __STR_H_
#define __STR_H_

#include<stddef.h>
#include<stdint.h>

int strlen(const char *str);
int strcmp(const char *str1,const char *str2);
char *strtok(char *str,const char *delim);

#endif
