/**
 *   \file jmp.c
 *   \brief source code file
 * source code to test setjmp() and longjmp()
 */

#include <setjmp.h>

#include "apue.h"

#define TOK_ADD 5

jmp_buf jmpbuffer;
void    do_line(char *);
void    cmd_add(void);
int     get_token(void);

int main(int argc, char *argv[]) {
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0) {
        printf("error\n");
    }
    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }

    return 0;
}

char *tok_ptr;

/* process one line of input */
void do_line(char *ptr) {
    int cmd;

    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch (cmd) { /* onecase for each command */
            case TOK_ADD: {
                cmd_add();
                break;
            }
            default:
                break;
        }
    }
}

void cmd_add(void) {
    int token;

    token = get_token();
    /* reset of processing for this command */
}

int get_token(void) {
    /* fetch next token from line pointed to by tok_ptr */
    return 0;
}
