#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counters[3] = {0, 0, 0};
int sigs[3] = {SIGUSR1, SIGUSR2, SIGALRM};

static void handler(int sig) {
    // printf("Ouch\n");
    for(int i = 0; i < 3; i++) {
        if(sig == sigs[i]) counters[i] += 1;
    }
}

int main(int argc, char *argv[]) {

    for(int i = 0; i < 3; i++) {
        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_SIGINFO;
        sa.sa_handler = handler;
        sigaction(sigs[i], &sa, NULL);
    }

    for(int i = 0; i < 3; i++) {
        if(fork() == 0) {
            for(int j = 0; j < atoi(argv[i + 1]); j++) {
                kill(getppid(), sigs[i]);
                sleep(1);
            }
            exit(0);
        }
    }

    for(int j = 0; ; j++) {
        printf("%i:\nSIGUSR1: %i\nSIGUSR2: %i\nSIGALRM: %i\n", j, counters[0], counters[1], counters[2]);
        sleep(1);
    }

}
