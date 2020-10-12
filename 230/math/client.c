#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

struct expr {
    int isFlag;
    char flag[300];

    int left;
    char op;
    int right;
};

int makeConn(char *addr, int port);
int exchange(int socket_desc, char* message, char* response, int len);
int readToken(char *str, int start, char* out);
int parse(char *str, struct expr* out);
int solve(struct expr *e);
void getFlag(char *id, int port, char *addr, char *out);

int main(int argc, char *argv[]) {
    
    char flag[200];
    if(argc < 4) {
        printf("Incorrect usage\n");
        return -1;
    }

    getFlag(argv[1], atoi(argv[2]), argv[3], flag);
    printf("FLAG: %s\n", flag);

    return 0;
    
}

//main program loop
void getFlag(char *id, int port, char *addr, char *out) {
    int sockdesc = makeConn(addr, port);
    char message[100];
    char resp[500];
    struct expr e;

    snprintf(message, 100, "cs230 HELLO %s\n", id);
    exchange(sockdesc, message, resp, 500);

    int i = 0;
    while(parse(resp, &e) != 1) {
        i++;
        int sol = solve(&e);
        printf("%i: %i %c %i = %i\n", i, e.left, e.op, e.right, sol);
        snprintf(message, 100, "cs230 %i\n", sol);
        exchange(sockdesc, message, resp, 500);
    }

    strcpy(out, e.flag);

}

//reads problem string puts in expr stru
int parse(char *str, struct expr* out) {
    char token[200];
    int i = readToken(str, 6, token); //skip 'cs230 '
    if(strcmp(token, "STATUS") == 0) {
        i = readToken(str, i + 1, token);
        out->left = atoi(token);

        i = readToken(str, i + 1, token);
        out->op = token[0];

        readToken(str, i + 1, token);
        out->right = atoi(token);
        return 0;
    } else {
        out->isFlag = 1;
        strcpy(out->flag, token);
        return 1;
    }
}

//solve problem given expression struct
int solve(struct expr *e) {
    switch (e->op)
    {
        case '+':
            return e->left + e->right;
        case '-':
            return e->left - e->right;
        case '*':
            return e->left * e->right;
        case '/':
            return e->left / e->right;
        default:
            return -420;
    }
}

//reads one token into out, returns final index
int readToken(char *str, int start, char* out) {
    int i = start;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') {
        out[i - start] = str[i];
        i++;
    }
    out[i - start] = '\0';
    return i;
}

//returns socket desc
int makeConn(char *addr, int port) {
    int sockdesc;
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if((sockdesc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
        printf("socket error\n");
        return -1;
    }
    if(connect(sockdesc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("connect error\n");
        return -1;
    }
    return sockdesc;
}

//send a message, take a response
int exchange(int socket_desc, char* message, char* response, int len) {
    if(send(socket_desc, message, strlen(message), 0) < 0) {
        printf("send error");
        return -1;
    }
    if(recv(socket_desc, response, len, 0) < 0) {
        printf("recieve error");
        return -1;
    }
    return 0;
}