#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "words.h"
#include "freaker.h"


int main(int argc, char *argv[]) {
    struct Word *words = NULL;
    char *envInp = getenv("WORD_FREAK");
    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            int file = open(argv[i], O_RDONLY);
            words = freak(file, words);
            close(file);
        }
    } else if (envInp != NULL) {
        int file = open(envInp, O_RDONLY);
        words = freak(file, words);
        close(file);
    } else {
        words = freak(STDIN_FILENO, words);
    }
    displayWords(words);
}
