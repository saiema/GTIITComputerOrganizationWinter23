#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LIFES 3
#define MAX_PATIENCE 3
static int lifes = MAX_LIFES;
static int patience = MAX_PATIENCE;

void pleaseSpareMe(int sig) {
    if (sig == SIGTERM) {
        signal(SIGTERM, pleaseSpareMe);
        if (lifes >= 3) puts("No please, don't kill me!!!");
        else if (lifes == 2) puts("No no wait! I'll be a good process!");
        else if (lifes == 1) puts("Nooooooo!");
        else puts("Aghhhhh!");
        fflush(stdout);
        if (lifes == 0) {
            exit(sig);
        }
        lifes--;
    }
}

void dontInterrupMe(int sig) {
    if (sig == SIGINT) {
        signal(SIGINT, dontInterrupMe);
        if (patience >= 3) puts("Ey!, I'm talking!");
        else if (patience == 2) puts("Don't Interrupt me, it's rude!");
        else if (patience == 1) puts("I'm loosing my patience!");
        else puts("I had enough!");
        fflush(stdout);
        if (patience == 0) {
            exit(sig);
        }
        patience--;
    }
}

void main(void) {
    signal(SIGTERM, pleaseSpareMe);
    signal(SIGINT, dontInterrupMe);
    while(1) {
        puts("Life's good, hope nobody tries to kill me :)");
        sleep(1);
    }
}