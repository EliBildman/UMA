#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"


struct Connection *noConn = NULL;

//Goal: create a room
//Params:
//  name: name of room
//  description: short description of room
//  altDescription: alternative description of room if changeable
//  num: unique id of room
//Returns: pointer to room
struct Room *makeRoom(char * name, char * description, char *altDescription, int num) {

    if(noConn == NULL) {
        noConn = (struct Connection *) malloc(sizeof(struct Connection));
        noConn->open = 0;
        strcpy(noConn->message, "You can't go that way.");
    }

    struct Room * r = (struct Room *) malloc(sizeof(struct Room));
    
    strcpy(r->name, name);
    strcpy(r->description, description);
    if(altDescription !=  NULL) strcpy(r->altDescription, altDescription);

    r->items = makeInv(3);
    r->num = num;
    r->altered = 0;
    r->north = r->south = r->east = r->west = r->up = r->down = noConn;
    
    return r;

}

//Goal: put an item in a room
//Params:
//  item: item to be put
//  room: room to be put in
void putInRoom(struct Item *item, struct Room *room) {
    putInInv(item, room->items);
}

//Goal: pop an item from a room
//Params:
//  name: name of item
//  room: room to be taken from
//Returns: pointer to item
struct Item * getFromRoom(char *name, struct Room *room) {
    return getFromInv(name, room->items);
}

//Goal: link two rooms together with a connection
//Params:
//  target: first room
//  link: second room
//  dir: char representing direction of link (north, west, etc)
void linkRooms(struct Room * target, struct Room * link, char dir) {
    
    struct Connection *conn = (struct Connection *) malloc(sizeof(struct Connection));
    *conn = (struct Connection) {target, link, 1, '\0'};
    
    switch(dir) {
        case 'n':
            target->north = link->south = conn;
            break;
        case 's':
            target->south = link->north = conn;
            break;
        case 'w':
            target->west = link->east = conn;
            break;
        case 'e':
            target->east = link->west = conn;
            break;
        case 'u':
            target->up = link->down = conn;
            break;
        case 'd':
            target->down = link->up = conn;
            break;
    }
    
}

//Goal: opens connection off a room
//Params:
//  room: room being targeted
//  dir: direction off room to be opened
void openConn(struct Room *room, char dir) {
    switch(dir) {
        case 'n':
            room->north->open = 1;
            break;
        case 's':
            room->south->open = 1;
            break;
        case 'w':
            room->west->open = 1;
            break;
        case 'e':
            room->east->open = 1;
            break;
        case 'u':
            room->up->open = 1;
            break;
        case 'd':
            room->down->open = 1;
            break;
    }
}

//Goal: move over a connection to another room
//Params:
//  r: room being moved from
//  connection: connection off r being moved over
//Returns: pointer to room moved to
struct Room *useConn(struct Room *r, struct Connection *c) {
    return c->a == r ? c->b : c->a;
}

//Goal: switch open flag on connection
//Params:
//  con: connection to be closed
//  message: message to be displayed when a user tries to use the connection
void lock(struct Connection *con, char *message) {
    con->open = 0;
    strcpy(con->message, message);
}

//Goal: get room description
//Params:
//  r: room to get description from
//Returns: description of r, concious of state
char *roomDesc(struct Room *r) {
    return r->altered ? r->altDescription : r->description;
}

