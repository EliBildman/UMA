#include <iostream>
#include <map>
#include <set>
#include <unistd.h>

void foo(void * x) {
    printf("%d\n", ((struct) x).a);
}

int main() {
    foo({a: 5});
}

