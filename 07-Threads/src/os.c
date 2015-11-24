#include <stddef.h>
#include <stdint.h>
#include "reg.h"
#include "threads.h"
#include "io.h"
#include "str.h"
#include "shell.h"

/* Filesystem includes*/
#include "filesystem.h"
#include "romfs.h"
extern const unsigned char _sromfs;


static void clear_input(char input_byte[],int index)
{

    while(index) {
        input_byte[index--] = '\0';
    }
}



void Shell_Task(void *userdata)
{
    int index = 0;
    char input_byte[128];
    char *argv[20];

    while(1) {
        print_str("sunny@mini-arm-os:~$");
        index = 0;
        while(1) {

            input_byte[index] = get_byte();
            /* Detect user press "enter" or a new line character*/
            if(input_byte[index] == '\r' || input_byte[index] == '\n') {
                if(index != 0) {
                    input_byte[index] = '\0';
                    /* Parse command,know argc and save input_byte to *argv[] */
                    int n = parse_command(input_byte, argv);
                    print_str("\n");
                    /*Function pointer to point what command is matched*/
                    cmdfunc *fptr = do_command(argv[0]);
                    if(fptr != NULL) {
                        fptr(n,argv);  /* Cmmand is doing now */
                    } else {
                        print_str("command not found!!");
                    }
                }
                print_str("\n");
                break;
            }
            /* Detect backspace */
            else if(input_byte[index] == 8 || input_byte[index] == 127) {
                if(index!=0) {
                    print_str("\b");
                    print_str(" ");
                    print_str("\b");
                    input_byte[index--] = '\0';
                }
            } else {
                print_str(&input_byte[index++]);

            }
        }
        clear_input(input_byte,index);
    }

}

/* 72MHz */
#define CPU_CLOCK_HZ 72000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

int main(void)
{
    const char *str1 = "Shell Task";

    usart_init();

    fs_init();
    register_romfs("romfs", &_sromfs);

    if (thread_create(Shell_Task, (void *) str1) == -1)
        print_str("Shell Thread creation failed\r\n");

    /* SysTick configuration */
    *SYSTICK_LOAD = (CPU_CLOCK_HZ / TICK_RATE_HZ) - 1UL;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 0x07;

    thread_start();

    return 0;
}
