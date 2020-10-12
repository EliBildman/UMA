char * getWord(char *sen, int n) {
    int a = -1;
    int b = -1;
    for(int i = 0; i < n + 1; i++) {
        a = ++b;
        if(sen[a] == '\0') {
            char * def = (char *) malloc(sizeof(char));
            *def = '\0';
            return def;
        }
        while(sen[b] != ' ' && sen[b] != '\0') b++;
    }
    char *word = (char *) calloc(sizeof(char), b - a + 1);
    for(int i = 0; i < b - a; i++) {
        word[i] = sen[a + i];
    }
    word[b - a] = '\0';
    return word;
}
