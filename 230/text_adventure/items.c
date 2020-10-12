#include <string.h>
#include <stdlib.h>
#include "items.h"

//Goal: create an Item
//Params:
//  name: name of item
//  description: short description of item
//  interRoom: id of room this item interacts with
//  useMessage: message displayed when item is successfully used
//  action: coded action to be taken by item when used
//  id: unique id for item
//Returns: pointer to item
struct Item * makeItem(char *name, char *description, int interRoom, char *useMessage, char *action, int id) {
    
    struct Item * i = (struct Item *) malloc(sizeof(struct Item));
    
    strcpy(i->name, name);
    strcpy(i->description, description);
    strcpy(i->useMessage,useMessage);
    strcpy(i->action, action);
    
    i->interRoom = interRoom;
    i->id = id;
    
    return i;
}

//Goal: make an inventory
//Params:
//  len: length of inventory
//Returns: pointer to inventory
struct Inventory * makeInv(int len) {
    struct Inventory * inv = (struct Inventory *) malloc(sizeof(struct Inventory));
    inv->len = len;
    inv->items = (struct Item **) calloc(sizeof(struct Item), len);
    inv->filled = (int *) calloc(sizeof(int), len);
    for(int i = 0; i < len; i++) inv->filled[i] = 0;
    return inv;
}

//Goal: put an item in an inventory
//Params:
//  item: item to be inserted
//  inv: inventory to be inserted into
//Returns: 1 if successful, 0 if not
int putInInv(struct Item *item, struct Inventory *inv) {
    for(int i = 0; i < inv->len; i++) {
        if(inv->filled[i] == 0) {
            inv->items[i] = item;
            inv->filled[i] = 1;
            return 1;
        }
    }
    return 0;
}

//Goal: pop an item from an inventory
//Params:
//  name: name of item
//  inv: inventory to be removed from
//Returns: pointer to item
struct Item * getFromInv(char *name, struct Inventory *inv) {
    for(int i = 0; i < inv->len; i++) {
        if(inv->filled[i] && strcmp(inv->items[i]->name, name) == 0) {
            inv->filled[i] = 0;
            return inv->items[i];
        }
    }
    return NULL;
}