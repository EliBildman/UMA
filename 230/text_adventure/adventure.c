#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rooms.h"

//*************************************************************//
//VIDEO DEMONSTRATION: https://youtu.be/0LONqdnY-qg
//*************************************************************//

//Goal: take item from room based on name and put in inventory
//Params:
//  room: room to be taken from
//  name: name of item
//  inv: player inventory
void takeItem(struct Room *room, char *name, struct Inventory * inv) {
    struct Item *item = getFromRoom(name, room);
    if(item != NULL) {
        if(putInInv(item, inv)) {
            printf("You picked up a %s.\n", name);
        } else {
            printf("You don't have any room to carry that.\n");
        }
    } else {
        printf("There is no %s here.\n", name);
    }
 }

//Goal: use item based on item functionality
//params:
//  item: item to be used
// room: current room
//Returns: 1 if successful, 0 if not
int useItem(struct Item *item, struct Room *room) {
    if(item->interRoom == room->num) {
        printf("%s\n", item->useMessage);
        room->altered = 1;
        if(item->action[0] == 'o') {
            openConn(room, item->action[1]);
        }
        return 1;
    } else {
        printf("There's nothing to do with that here.\n");
        return 0;
    }
}

//Goal: drop specific item from inventory to room
//Params:
//  item: name of item to be dropped
//  inv: player inventory
//  room: room to be dropped into
void dropItem(char *item, struct Inventory *inv, struct Room *room) {
    struct Item *i =  getFromInv(item, inv);
    if(i != NULL) {
        putInRoom(i, room);
        printf("You dropped the %s.\n", item);
    } else {
        printf("You dont have that item on you.\n");
    }
}

// Goal: execute player move command
// Params:
//  from: room player is currently in
//  to: connetion player wants to move towards
//Returns: room player is in after move command executes
struct Room * moveTo(struct Room *from, struct Connection *dir) {
    if(dir->open) {
        struct Room *to =  useConn(from, dir);
        printf("%s\n", roomDesc(to));
        return to;
    }
    printf("%s\n", dir->message);
    return from;
}

//Goal: execute full player turn from input->output
//Params: 
//  room: pointer to pointer of current room
//  inv: player inventory
void playerTurn(struct Room **room, struct Inventory *inv) {
    
    printf(": ");
    char command[20];
    
    scanf("%s", command);

    if(strcmp(command, "look") == 0) {
        printf("%s\n", roomDesc(*room));
    } else if (strcmp(command, "take") == 0) {
        char item[20];
        scanf("%s", item);
        takeItem(*room, item, inv);
    } else if (strcmp(command, "use") == 0) {
        char item[20];
        scanf("%s", item);
        struct Item * i = getFromInv(item, inv);
        if(i != NULL) {
            if(!useItem(i, *room)) {
                putInInv(i, inv);
            }
        } else {
            printf("You don't have that item with you.\n");
        }
    } else if (strcmp(command, "drop") == 0) {
        char item[20];
        scanf("%s", item);
        dropItem(item, inv, *room);
    } else if (strcmp(command, "go") == 0) {
        char dir[20];
        scanf("%s", dir);
        if (strcmp(dir, "north") == 0) {
            *room = moveTo(*room, (*room)->north);
        } else if (strcmp(dir, "south") == 0) {
            *room = moveTo(*room, (*room)->south);
        } else if (strcmp(dir, "east") == 0) {
            *room = moveTo(*room, (*room)->east);
        } else if (strcmp(dir, "west") == 0) {
            *room = moveTo(*room, (*room)->west);
        } else if (strcmp(dir, "up") == 0) {
            *room = moveTo(*room, (*room)->up);
        } else if (strcmp(dir, "down") == 0) {
            *room = moveTo(*room, (*room)->down);
        } else {
            printf("That's not a direction you can move in.\n");
        }
    } else {
        printf("That doesn't mean anything here...\n");
    }
    
}


// Goal: Create a map of rooms according to map
//       [Forest]
//       [Backyard]
//          (up)
//        [Small Room][Dungeon][Closet]
//          [Balcony]  (down)
//            (up)    [Bedroom]
//        [Grand Room][Hallway]
//         [Entrance]
// Returns: pointer to entrance room
struct Room * createRooms() {
    struct Room *r;
    struct Item * items;

    
    struct Room *start = makeRoom("Entrance", "You stand at the entrace to a castle to your north. You should enter: they'll be back soon.", NULL, 1);

    linkRooms(start, makeRoom("Grand Room", "You're in the center of a massive room, the walls are covered in beautiful paintings and gold. A hallway opens to the east, stairs run up to a balcony above.", NULL, 2), 'n');

    r = useConn(start, start->north);
    
    linkRooms(r, makeRoom("Balcony", "You're on a balcony looking over the Grand Room. There's nowhere to go but back down. A lone table sits near the edge with an empty wine bottle on it.", "You're on a balcony looking over the Grand Room. There's nowhere to go but back down. A lone table sits near the edge empty now.", 3), 'u');
    putInRoom(makeItem("bottle", "An empty wine bottle, looks old.", 5, "You throw the wine bottle across the room, it clanks loudly in a corner. The gaurd stirs at the noise, and crosses the room to inspect. On finding the bottle he shrugs, burps, and falls asleep on the floor.", "od", 1), useConn(r, r->up));


    linkRooms(r, makeRoom("Hallway", "You're in a hallway. It's much shorter than it looked from the outside. There's one door on the north side.", NULL, 4), 'e');
    r = useConn(r, r->east);

    linkRooms(r, makeRoom("Bedroom", "You've entered a gaurd's bedroom and he's asleep on the bed! There's a trap door in the floor but you can't open it without waking the gaurd. You can't read very well right now, but 5 words sit on a banner across from you.", "You've entered a gaurd's bedroom. No one is home", 5), 'n');
    r = useConn(r, r->north);

    linkRooms(r, makeRoom("Dungeon", "You're in what looks like a dungeon. Fluorescent lights hang from the ceiling. Tables spread across the room, all are empty but one that holds a small knife. A closet door hangs ajar to the east and a smaller room opens to the west.", "You're in what looks like a dungeon. Fluorescent lights hang from the ceiling. Tables spread across the room, all are empty. A closet door hangs ajar to the east and a smaller room opens to the west.", 6), 'd');
    lock(r->down, "You can't get to the trap door because the gaurd is in the way.");
    r = useConn(r, r->down);
    putInRoom(makeItem("knife", "A dagger with a small πKA enscribed on the handle.", 9, "You muster all your courage and rush across the yard knife in hand. The gaurd sees you coming, yells \"what the fuck bro!\" and runs away.", "on", 2),r);

    linkRooms(r, makeRoom("Closet", "You're crammed in a closet. It's dark. A key lies at your feet.", "You're crammed in a closet. It's dark.", 7), 'e');
    putInRoom(makeItem("key", "A golden key! It's attached to a circular ribbon of sorts.", 8, "You use the key to unlock the gate.", "ou", 3), useConn(r, r->east));

    linkRooms(r, makeRoom("Small Room", "You're in a room with a small set of stairs up to a gate. The gate looks locked.", "You're in a room with a small set of stairs up to a gate. The gate lies open.", 8), 'w');
    r = useConn(r, r->west);

    linkRooms(r, makeRoom("Backyard", "You're in the back garden of the catle. The forest lies just to your north, but before it is a gaurd. He stares at you, confused.", "You're in the back garden of the catle. The forest lies just to your north, unobstructed.", 9), 'u');
    lock(r->up, "The gate is locked.");
    r = useConn(r, r->up);

    linkRooms(r, makeRoom("Forest", "You're in the trees behind the frat house. The grass is dead and the scent of beer lingers. You realize you're probably not getting a bid.", NULL, 10), 'n');
    lock(r->north, "You're too scared to try to walk past the gaurd.");
    
    return start;

}

//Goal: run main game loop until game is completed
void runGame() {
    struct Inventory * inv = makeInv(3);
    struct Room **r = (struct Room **) malloc(sizeof(struct Room *));
    *r = createRooms();
    printf("\n---------- CASTLE ADVENTURE ----------\n           by Eli Bildman\n\nPress [ENTER] to start...");
    getchar();
    printf("\n\n%s\n", roomDesc(*r));
    while((*r)->num != 10) playerTurn(r, inv);
    printf("\n---------- GAME OVER ----------\n");
    free(inv);
    free(r);
}


int main() {
    runGame();
    return 0;
}
