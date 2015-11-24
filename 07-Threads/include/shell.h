#ifndef __SHELL_H_
#define __SHELL_H_

typedef void cmdfunc(int, char*[]);

int parse_command(char *str,char *argv[]);
cmdfunc *do_command(const char *str);

#endif
