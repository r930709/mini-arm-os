#include "str.h"
#include "io.h"

int strlen(const char *str)
{
    int count = 0;
    while(*str++ != '\0') {
        count++;
    }
    return(count);
}
int strcmp(const char *str1,const char *str2)
{

    while(*str1 != '\0' && *str2 !='\0') {
        if(*(str1++) != *(str2++)) {
            return(1);
        }
    }
    return(0);
}
char *str_temp_head = NULL;

char *strtok(char *str,const char *delim)
{

    int i;
    int len = strlen(delim);

    if(len==0) {
        print_str("delimiters are empty\n");
    }

    if(!str_temp_head && !str) {
        return(NULL);
    }
    if(!str_temp_head && str) {
        str_temp_head = str;
    }
    /*Find the start of the substring, skip delimiters*/
    char *p_start = str_temp_head;
    while(1) {
        for(i=0 ; i < len ; i++) {
            if(*p_start == *(delim+i)) {
                p_start++;
                break;
            }
        }
        /*Scan complete,modify string temp head */
        if(i == len) {
            str_temp_head = p_start;
            break;
        }
    }
    /*return NULL if nothing left*/
    if(*str_temp_head == '\0') {
        str_temp_head = NULL;
        return(str_temp_head);
    }
    /*Find the end of the substring,and replace the delimiter with '\0' */
    while(*str_temp_head != '\0') {
        for(i=0 ; i<len; i++) {
            if(*str_temp_head == *(delim+i)) {
                *str_temp_head = '\0';
                break;
            }
        }
        str_temp_head++;
        if(i < len) {
            break;
        }
    }
    return (p_start);
}
