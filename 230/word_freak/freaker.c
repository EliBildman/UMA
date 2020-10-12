#include "words.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char nonWords[50] = " .,?!\n\t\r\f:;\"/\\'[]{}()";

//goal: determine if character represents a break between words
//params:
//  c: character to be analized
int nonWordChar(char c) {
    int i = 0;
    while(nonWords[i] != '\0') {
        if(nonWords[i] == c) return 1;
        i++;
    }
    return 0;
}

//goal: find the freqencies of every word in a file
//params:
//  file: file descriptor to be scanned
//  words: struct Word linked list to append words to
//returns: head of words linked list after scan
struct Word * freak(int file, struct Word *words) {
    char buff[1];
    int currSize = 10;
    char *currWord = (char *) calloc(sizeof(char), currSize);
    int i = 0;
    while(read(file, buff, 1) != 0) {
        if(i >= currSize) {
            currSize *= 2;
            currWord = realloc(currWord, sizeof(char) * currSize);
        }
        if(nonWordChar(*buff)) {
            currWord[i] = '\0';
            if(i > 0) words = addWord(words, currWord);
            i = 0;
        } else {
            currWord[i++] = buff[0];
        }
    }
    return words;
}