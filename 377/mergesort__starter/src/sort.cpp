#include "sort.h"

int run(int argc, char* argv[]){
  if(argc < 2){
    cerr << "Wrong number of inputs, need at least one num to sort." << endl;
    cerr << "Example call: " << argv[0] << " 3 2 1" << endl;
  }

  if(argc <= 3){
    sort(argc-1, &argv[1]);
  } else {
    split_and_merge(argc-1, &argv[1], argv[0]);
  }
  return 0;
}

void sort(int count, char* argv[]){
  // covert to ints (n*O(1) = O(n))
  int nums[count];
  for(int i = 0; i < count; i++){
    try{
      nums[i] = stoi(argv[i]);
    } catch(...){
      string s = "Found something that isn't an int: ";
      s += argv[i];
      cout << s << endl;
    }
  }
  
  ofstream myfile;
  myfile.open("temp/" + to_string(getpid()) + ".txt");

  // Write sorted output to file (n*O(1) = O(n))
  if(count == 1){
    myfile << nums[0] << endl;
  }
  // case of 2 sorted
  else if(nums[0] < nums[1]){
    myfile << nums[0] << endl;
    myfile << nums[1] << endl;
  }
  // case of 2 unsorted
  else{
    myfile << nums[1] << endl;
    myfile << nums[0] << endl;
  }
  myfile.close();
}

void split_and_merge(int argc, char* argv[], char* name){

  const int half_size = argc / 2;
  vector<char*> argv_vector1;
  vector<char*> argv_vector2;
  argv_vector1.push_back(name);
  for(int i = 0; i < half_size; i++){
    argv_vector1.push_back(argv[i]);
  }
  argv_vector2.push_back(name);
  for(int i = half_size; i < argc; i++){
    argv_vector2.push_back(argv[i]);
  }
  argv_vector1.push_back(NULL);
  argv_vector2.push_back(NULL);

  
  char** argv_child1 = &argv_vector1[0];
  char** argv_child2 = &argv_vector2[0];

  // Fork the processes and run on subset (O(1))
  int child1, child2; 
  fork_and_wait(argv_child1, argv_child2, name, &child1, &child2);
  
  // Read in results of children
  vector<int> split_lo = read_vector_from_file(child1);
  vector<int> split_hi = read_vector_from_file(child2);

  // Remove now unused files
  remove(("temp/" + to_string(child1) + ".txt").c_str());
  remove(("temp/" + to_string(child2) + ".txt").c_str());

  // combine (log(n)*O(n) = O(nlog(n)))
  vector<int> ret = combine_sorted(split_lo, split_hi);
  
  // write to file (O(n))
  ofstream myfile;
  myfile.open("temp/" + to_string(getpid()) + ".txt");
  for(int i : ret){
    myfile << to_string(i) << endl;
  }
  myfile.close();
}

void fork_and_wait(char** argv1, char** argv2, char* name, int* pid1, int* pid2){
  // TODO: Fork processes
  int child1;
  int child2;
  if((child1 = fork()) == 0) {
    //child
    // *pid1 = getpid();
    execvp(name, argv1);
    exit(0);
  } else if ((child2 = fork()) == 0) {
    //child2

    execvp(name, argv2);
    exit(0);
  } else {
    //parent
    *pid1 = child1;
    *pid2 = child2;
    waitpid(*pid1, NULL, 0);
    waitpid(*pid2, NULL, 0);
  }

  
  // TODO: Wait for children to complete
}

vector<int> read_vector_from_file(int pid){
  vector<int> output;
  ifstream myfile;
  myfile.open("temp/" + to_string(pid) + ".txt");
  string num;
  while(getline(myfile, num)){
    output.push_back(stoi(num));
  }
  myfile.close();
  return output;
}

vector<int> combine_sorted(vector<int>& one, vector<int>& two){
  vector<int> ret;
  size_t lo = 0, hi = 0;
  for(; lo < one.size() && hi < two.size();){
    if(one.at(lo) < two.at(hi)){
      ret.push_back(one.at(lo));
      lo++;
    } else {
      ret.push_back(two.at(hi));
      hi++;
    }
  }
  while(lo < one.size()){
    ret.push_back(one.at(lo));
    lo++;
  }
  
  while(hi < two.size()){
    ret.push_back(two.at(hi));
    hi++;
  }
  return ret;
}