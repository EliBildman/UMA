#include "../src/sallocator.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TEST(SallocTest, SallocTest1) {
    // Init Simple Allocator object
    Sallocator my_alloc(100);

    // Allocate all memory in small chunks
    for(int i = 0; i < 19; i++){
        my_alloc.allocate(5);
    }
    for(int i = 0; i < 5; i++){
        my_alloc.allocate(1);
    }
    for(int i = 0; i < 19; i++){
        my_alloc.free(i*5, 5);
    }
    for(int i = 0; i < 5; i++){
        my_alloc.free(95+i, 1);
    }


    ASSERT_EQ(true, my_alloc.allocate(100));
    ASSERT_EQ(false, my_alloc.allocate(1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
