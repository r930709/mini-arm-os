#include "type.h"

int atoi(const char *str)
{
    int result = 0;
    while(*str != '\0') { //Check whether a string tail
        result = result * 10;  //Become to a Decimal number
        int compare = *str - '0';  //Get the number by comparing the ascii code

        result = result + compare;
        ++str;
    }
    return(result);
}

char *itoa(int num,char *str)
{
    char const digit[] = "0123456789";
    char *p = str;
    if(num<0) {
        *p++ = '-';
        num*= -1;
    }
    int shifter = num;
    do {
        /*Move to where representation ends*/
        ++p;
        shifter = shifter/10;

    } while(shifter);
    *p = '\0';
    do {
        /*Move back,fill number into the char pointer*/
        *--p = digit[num%10];
        num = num/10;

    } while(num);
    return(str);
}
