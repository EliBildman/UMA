#include "items.h"

struct Room {

    char name[20];
    char description[300];
    char altDescription[300];
    int altered;

    int num;

    struct Connection *north;
    struct Connection *south;
    struct Connection *west;
    struct Connection *east;
    struct Connection *up;
    struct Connection *down;

    struct Inventory *items;

};

struct Connection {
    
    struct Room *a;
    struct Room *b;
    int open;
    char message[75];
    
};

struct Room * makeRoom(char *name, char *description, char *altDescription, int num);

void linkRooms(struct Room *, struct Room *, char);
struct Room  *useConn(struct Room *r, struct Connection *c);
void openConn(struct Room *room, char dir);
void lock(struct Connection *con, char *message);
char *roomDesc(struct Room *r);
void putInRoom(struct Item *item, struct Room *room);
struct Item *getFromRoom(char *name, struct Room *room);