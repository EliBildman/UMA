#include "../src/sort.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TEST(SortTest, SortTest1) {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(6);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(4);
    nums.push_back(0);

    pthread_t id;
    pthread_create(&id, NULL, sort, &nums);
    pthread_join(id, NULL);

    EXPECT_EQ(nums.size(), 8);
    for(size_t i = 0; i < nums.size()-1; i++){
        EXPECT_EQ(nums[i], i);
    }
    EXPECT_EQ(nums[7], 6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
