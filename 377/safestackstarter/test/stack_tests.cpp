#include "../src/SafeStack.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream file("output.txt");
pthread_mutex_t write_lock;
SafeStack nums;

void* producer(void* param){
    for(int i = 0; i < 10; i++){
        nums.push(rand());
    }
    pthread_exit(0);
}

void* consumer(void* param){
    SafeStack &my_stack = *((SafeStack*)(param));
    for(int i = 0; i < 10; i++){
        pthread_mutex_lock(&write_lock);
        file << my_stack.pop() << endl;
        pthread_mutex_unlock(&write_lock);
    }
}

TEST(SortTest, SortTest1) {
    void* nums_ptr = ((void*)&nums);
    pthread_t pids[10];
    pthread_t cids[10];
    for(int i = 0; i < 10; i++){
        pthread_create(&pids[i], NULL, producer, nums_ptr);
    }

    for(int i = 0; i < 10; i++){
        pthread_create(&cids[i],NULL, consumer, nums_ptr);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(pids[i], NULL);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(cids[i], NULL);
    }

    ifstream infile("output.txt");
    string line;
    int i = 0;
    while(infile >> line){
        i++;
    }

    ASSERT_EQ(i, 100);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
