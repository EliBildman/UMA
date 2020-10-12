#include "sort.h"

int run(int argc, char* argv[]){
    if(argc < 2){
        cerr << "Wrong number of inputs, need at least one num to sort." << endl;
        cerr << "Example call: " << argv[0] << " 3 2 1" << endl;
    }

    // Load in nums
    vector<int> nums = load(argc-1, &argv[1]);
    
    // Spawn worker thread. (Not exclusively necessary, but otherwise we'd have to use return instead of pthread_exit())
    pthread_t id;
    pthread_create(&id, NULL, sort, &nums);
    pthread_join(id, NULL);
    cout << "done:" << endl;
    for(int i : nums){
        cout << i << endl;
    }
    return 0;
}

vector<int> load(int count, char* argv[]){
    vector<int> nums;
    for(int i = 0; i < count; i++){
        nums.push_back(stoi(argv[i]));
    }
    return nums;
}

void* sort(void* arg){
    vector<int> &nums = *((vector<int>*)(arg));
    // Base case
    if(nums.size() <= 2){
        if(nums.size() <= 1){
            pthread_exit(NULL);
        } else if(nums[0] < nums[1]){
            pthread_exit(NULL);
        } else{
            int temp = nums[0];
            nums[0] = nums[1];
            nums[1] = temp;
            pthread_exit(NULL);
        }
    }
    
    // Not base case:
    // split:
    size_t const half_size = nums.size() / 2;
    vector<int> left(nums.begin(), nums.begin() + half_size);
    vector<int> right(nums.begin() + half_size, nums.end());

    // TODO: Make two threads which call sort() on their respective halves
    // Also join them.

    pthread_t tids[2];

    pthread_create(tids, NULL, sort, &left);
    pthread_create(tids + 1, NULL, sort, &right);

    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);


    // Merge:
    int k = 0;
    size_t i = 0, j = 0;
    while(i < left.size() && j < right.size()){
        if(left[i] < right[j]){
            nums[k++] = left[i++];
        } else {
            nums[k++] = right[j++];
        }
    }

    while(i < left.size()){
        nums[k++] = left[i++];
    }
    while(j < right.size()){
        nums[k++] = right[j++];
    }
    pthread_exit(NULL);
}