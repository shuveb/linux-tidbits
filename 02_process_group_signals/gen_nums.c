#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define MIN_RAND_NUM 0
#define MAX_RAND_NUM 100

int tty_fd;

void open_tty() {
   tty_fd = open("/dev/tty", O_WRONLY);
   if (tty_fd < 0) {
       fprintf(stderr, "Error opening TTY.\n");
       exit(1);
   }
}

void print_to_tty(char *s) {
    int len = strlen(s);
    write(tty_fd, s, len);
}

void sigint_handler(int signo) {
    print_to_tty("get_nums got SIGINT. Will exit...\n");
    exit(0);
}

void print_process_group_info() {
    char str[128];
    memset(str, 0, sizeof(str));
    snprintf(str, sizeof(str), "gen_nums: PID: %d, PGID: %d\n", getpid(), getpgrp());
    print_to_tty(str);
}

int main() {
    print_process_group_info();
    srand(time(NULL));

    open_tty();
    signal(SIGINT, sigint_handler);

    while(1) {
        int rand_num1 = (rand() % (MAX_RAND_NUM - MIN_RAND_NUM)) + MIN_RAND_NUM;
        int rand_num2 = (rand() % (MAX_RAND_NUM - MIN_RAND_NUM)) + MIN_RAND_NUM;
        printf("%d %d\n", rand_num1, rand_num2);
        fflush(stdout);
        sleep(1);
    }

    return 0;
}

#pragma clang diagnostic pop