
struct Word {
    char *string;
    int freq;
    struct Word *next;
};

struct Word * makeWord(char * name, struct Word *next);
int itt(struct Word * word);
void displayWords(struct Word *words);
struct Word *find(struct Word *words, char *word);
void printString(char *string);
void toString(int num, char *out);
struct Word * addWord(struct Word *words, char *word);