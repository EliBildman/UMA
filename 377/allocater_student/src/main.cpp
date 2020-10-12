#include "main.h"

int main(int argc, char** argv){
    for(int i = 0; i < 10; i++){
        my_alloc.allocate(10);
    }
    cout << "Done allocating. Free blocks:" << endl;
    my_alloc.print();
    for(int i = 0; i < 10; i++){
        my_alloc.free(i*10, 10);
    }
    cout << "Done freeing. Free blocks:" << endl;
    my_alloc.print();
    cout << (my_alloc.allocate(100) ? "First allocation succesful" : "First allocation unsuccessful. Something is wrong.") << endl;
    cout << "Free blocks after first allocation attempt:" << endl;
    my_alloc.print();
    cout << (my_alloc.allocate(1) ? "Second allocation succesful. Something has gone wrong." : "Second allocation unsuccessful.") << endl;
    cout << "Free blocks after second allocation attempt:" << endl;
    my_alloc.print();
}