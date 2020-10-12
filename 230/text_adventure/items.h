struct Item {
    
    char name[30];
    char description[100];
    
    int interRoom;
    char useMessage[300];
    char action[5];
    
    int id;
    
};

struct Inventory {

    struct Item **items;
    int len;
    int *filled;

};

struct Item  *makeItem(char* name, char* description, int interRoom, char *useMessage, char *action, int id);
struct Inventory * makeInv(int len);
int putInInv(struct Item *item, struct Inventory* inv);
struct Item * getFromInv(char *name, struct Inventory *inv);
