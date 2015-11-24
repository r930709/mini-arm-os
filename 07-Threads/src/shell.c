#include "shell.h"
#include <stddef.h>
#include <stdint.h>
#include "str.h"
#include "io.h"
#include "type.h"
#include "malloc.h"
#include "threads.h"
#include "filesystem.h"


typedef struct cmdlist {
    const char *name;
    cmdfunc *fptr;
    const char *detail;
} cmdlist;

void help_command(int n,char *argv[]);
void fib_command(int n,char *argv[]);
void ls_command(int n,char *argv[]);
extern int fibonacci(int x);

/* Use gcc token concatentation */
#define COMMAND(NAME,DETAIL) {.name=#NAME, .fptr=NAME ## _command, .detail=DETAIL}
#define getNumberInArray(a) (sizeof(a)/sizeof(a[0]))
char pwd[20] = "/romfs/";


cmdlist cl[]= {
    COMMAND(help, "Show the manual of the command"),
    COMMAND(fib, "Compute the fibonacii number,Example $fib -n=[number]"),
    COMMAND(ls, "List directory, Example $ls /romfs/")

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
void ls_command(int n, char *argv[])
{

    int dir;

    if(n == 1) {

        dir = fs_opendir(pwd);

    } else if(n == 2) {
        dir = fs_opendir(argv[1]);

    } else {
        print_str(" Too many argument!\r\n");
        return;
    }

    (void)dir;  //Use dir

}

void Fib_Task(void *userdata)
{

    int number = (int)userdata;
    char *result_str = malloc(4*sizeof(char));
    int result = fibonacci(number);
    result_str = itoa(result,result_str);
    print_str(result_str);
    free(result_str);
    result_str = NULL;

}


void fib_command(int n,char *argv[])
{

    char *num_str = malloc(1*sizeof(char));
    num_str = strtok(argv[1],"-n=\r\n");
    int number = atoi(num_str);
    if (thread_create(Fib_Task,(void *)number) == -1) {
        print_str("Fib_Task creation failed\r\n");
    }

}
