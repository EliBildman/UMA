#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int f = open(argv[1], O_RDONLY);
    ssize_t size = -1;
    int buffer_size = 100;
    while(size != 0) {
        char *buffer = (char *) calloc((sizeof(char)), buffer_size);
        size = read(f, buffer, buffer_size);
        printf("%s", buffer);
    }   
    close(f);
}