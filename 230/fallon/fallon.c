#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>

#include "fallon.h"

static int NUM_OPERATORS = 3;
static int NUM_LINES = 5;
static int connected = 0;  
static sem_t connected_lock;
static sem_t operators;  // Callers that are connected
    

void* phonecall(void* vargp) {
    pthread_t id = (int) pthread_self();
    int is_connected = 0;
    printf("Call recieved, ID: %lu\n", id);
    while(!is_connected) {
        sem_wait(&connected_lock);
        if(connected < NUM_LINES) {
            connected += 1;
            sem_post(&connected_lock);
            is_connected = 1;
            printf("Connected caller, ID %lu\n", id);
        } else {
            sem_post(&connected_lock);
        }
    }
    sem_wait(&operators);
    printf("Call taken by operator, ID %lu\n", id);
    sleep(3);
    printf("Ticket purchased, ID %lu\n", id);
    sem_post(&operators);

    sem_wait(&connected_lock);
    connected -= 1;
    sem_post(&connected_lock);
    printf("Caller disconnected: %lu\n", id);

    pthread_exit(NULL);
}

void makeCalls(int n) {
    pthread_t tids[n];
    for(int i = 0; i < n; i++) {
        struct args a;
        pthread_create(tids + i, NULL, phonecall, NULL);

    }
    for(int i = 0; i < n; i++) {
        pthread_join(tids[i], NULL);
    }
}

void initSems() {
    sem_init(&connected_lock, 0, 1);
    sem_init(&operators, 0, NUM_OPERATORS);
}

int main(int argc, char* argv[]) {
    initSems();
    if(argc > 1) {
        makeCalls(atoi(argv[1]));
    }
    return 0;
}