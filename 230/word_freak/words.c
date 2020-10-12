#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "words.h"
#include <string.h>

//goal: construct a Word struct
//params:
//  name: char list name of word
//  next: pointer to next word in linked list || NULL for end
//returns: Word pointer to created word
struct Word * makeWord(char * name, struct Word *next) {
    char *str = (char *) calloc(sizeof(char), strlen(name));
    struct Word * word = (struct Word *) malloc(sizeof(struct Word));
    strcpy(str, name);
    word->string = str;
    word->freq = 1;
    word->next = next;
    return word;
}

//goal: itterate a word structs freq variable
//params:
//  word: pointer to word struct to be intterated
//returns: new value of freq for given word
int itt(struct Word * word) {
    return ++word->freq;
}

//goal: display all words in linked list in "word : freq" format
//params:
//  words: linked list of word structs
void displayWords(struct Word *words) {
    int biggestWord = 0;
    int biggestFreq = 0;
    struct Word *curr = words;
    while(curr != NULL) {
        int wordlen = (int) strlen(curr->string);
        char freqStr[100];
        toString(curr->freq, freqStr);
        int freqlen = (int) strlen(freqStr);
        if(wordlen > biggestWord) biggestWord = wordlen;
        if(freqlen > biggestFreq) biggestFreq = freqlen;
        curr = curr->next;
    }
    curr = words;
    while(curr != NULL) {
        int wordlen = (int) strlen(curr->string);
        printString(curr->string);
        while(wordlen++ < biggestWord + 1)
            printString(" ");
        printString(":");
        char f[100];
        toString(curr->freq, f);
        int freqlen = (int) strlen(f);
        while(freqlen++ < biggestFreq + 1)
            printString(" ");
        printString(f);
        printString("\n");
        curr = curr->next;
    }
    printString("\n");
}

//goal: print given string to STDOUT
//params:
//  string: char list string to be printed, ending in \0
void printString(char* string) {
    write(STDOUT_FILENO, string, strlen(string));
}

//goal: convert integer into string
//params:
//  num: int to be converted
//  out: char list to be written to as output
void toString(int num, char *out) {
    if(num == 0) {
        strcpy(out, "0");
        return;
    }
    out[0] = '\0';
    int i = 0;
    while(num > 0) {
        for(int j = ++i; j > 0; j--) {
            out[j] = out[j - 1];
        }
        out[0] = (char) ((num % 10) + '0');
        num /= 10;
    }
}

//goal: add word to Words linked list, either by itterating matching word or creating new Word struct
//params:
//  words: linked list of Word structs
//  word: char list word to be added
//returns: head of linked list after appendage
struct Word * addWord(struct Word *words, char *word) {
    struct Word *w = find(words, word);
    if(w == NULL) {
        return makeWord(word, words);
    } else {
        itt(w);
        return words;
    }
}

//goal: find Word struct in linked list based of string
//params:
//  words: linked list of Word struts to be searched
//  word: char list word to be found
//retuns: pointer to Word struct found || NULL if not found
struct Word * find(struct Word *words, char *word) {
    while(words != NULL) {
        if(strcmp(words->string, word) == 0) return words;
        words = words->next;
    }
    return NULL;
}
