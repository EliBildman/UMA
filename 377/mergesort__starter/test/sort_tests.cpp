#include "../src/sort.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TEST(SortTest, SortTest1) {
    char* nums[] = {"./sort", "1", "6", "3", "2", "5", "4", "0"};
    run(8, nums);
    system("ls ./temp >files.txt");

    vector<int> filenames;
    ifstream files;
    files.open("files.txt");
    string num;
    while(getline(files, num)){
        filenames.push_back(stoi(num));
    }
    sort(filenames.begin(), filenames.end());
    
    ifstream output;
    output.open("./temp/" + to_string(filenames.back()) + ".txt");
    vector<int> output_nums;
    while(getline(output, num)){
        output_nums.push_back(stoi(num));
    }
    EXPECT_EQ(output_nums.size(), 7);
    for(size_t i = 0; i < output_nums.size(); i++){
        EXPECT_EQ(output_nums[i], i);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
