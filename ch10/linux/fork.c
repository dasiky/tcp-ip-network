#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int gval = 10;
int main(void) {
    pid_t pid;
    int lval = 20;
    gval++, lval += 5;
    pid = fork();
    if (pid == 0)
        gval += 2, lval += 2;
    else
        gval -= 2, lval -= 2;

    if (pid == 0)
        printf("child proc: %d  %d\n", gval, lval);
    else
        printf("parent proc: %d  %d\n", gval, lval);

    return 0;
}