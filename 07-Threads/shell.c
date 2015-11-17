#include "shell.h"
#include <stddef.h>
#include <stdint.h>
#include "str.h"
#include "io.h"
#include "type.h"
#include "malloc.h"
#include "threads.h"

typedef struct cmdlist {
    const char *name;
    cmdfunc *fptr;
    const char *detail;
} cmdlist;

void help_command(int n,char *argv[]);
void fib_command(int n,char *argv[]);
extern int fibonacci(int x);

/* Use gcc token concatentation */
#define COMMAND(NAME,DETAIL) {.name=#NAME, .fptr=NAME ## _command, .detail=DETAIL}
#define getNumberInArray(a) (sizeof(a)/sizeof(a[0]))

cmdlist cl[]= {
    COMMAND(help, "Show the manual of the command"),
    COMMAND(fib, "Compute the fibonacii number,Example $fib -n=[number]"),
};

int parse_command(char *str,char *argv[])
{
    int count = 0;
    argv[count] = strtok(str," ");
    while(argv[count] != NULL) {
        argv[++count] = strtok(NULL," ");
    }
    return(count);
}
cmdfunc *do_command(const char *cmd)
{
    int i;
    for(i = 0; i<getNumberInArray(cl); ++i) {
        if(strcmp(cl[i].name,cmd)==0) {
            return(cl[i].fptr);
        }
    }
    return(NULL);
}

void help_command(int n,char *argv[])
{
    int i;
    for(i =0; i<getNumberInArray(cl); i++) {
        print_str(cl[i].name);
        print_str(" - ");
        print_str(cl[i].detail);
        print_str("\n");
    }

}

void fib_command(int n,char *argv[])
{

    char *num_str = malloc(4*sizeof(char));
    num_str = itoa(n,num_str);
    print_str(argv[0]);
    print_str("\n");
    print_str(argv[1]);
    print_str("\n");
    print_str(num_str);
    print_str("\n");
}
