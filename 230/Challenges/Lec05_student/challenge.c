#include "challenge.h"

// goal: creates a Cred struct given the username, password, and next credential
// param username: char* representing the username
// param password: char* representing the password
// param next: Cred struct pointer representing the next credential
// return: a Cred struct pointer to a credential with the specified fields
//
// TODO: complete the function
struct Cred* cred(char* username, char* password, struct Cred* next)
{
  struct Cred *c;
  c->username = username;
  c->password = password;
  c->next = next;
  return c;
}

// goal: frees a list of credentials
// param head: pointer to first credential in the list
//
// TODO: complete the function
void cred_free(struct Cred* head)
{
  struct Cred *n;
  while(head != NULL) {
    n = head->next;
    free(head);
    head = n;
  }
}

// goal: gets the username from a Cred struct
// param head: pointer to a Cred struct
// return: a char* representing the username of the credential
//
// TODO: complete the function
char* get_username(struct Cred* node)
{
  return node->username;
}

// goal: gets the password from a Cred struct
// param node: pointer to a Cred struct
// return: a char* representing the password of the credential
//
// TODO: complete the function
char* get_password(struct Cred* node)
{
  return node->password;
}

// goal: gets the pointer to the next credential in a list
// param node: pointer to a Cred struct at the node of a list
// return: a pointer to the next Cred struct in the list
//
// TODO: complete the function
struct Cred* get_next(struct Cred* node)
{
  return node->next;
}

// goal: sets the username of a Cred struct
// param node: pointer to Cred struct to change username of
// param username: char* representing new username
//
// TODO: complete the function
void set_username(struct Cred* node, char* username)
{
  node->username = username;
}

// goal: sets the password of a Cred struct
// param node: pointer to Cred struct to change password of
// param password: char* representing new password
//
// TODO: complete the function
void set_password(struct Cred* node, char* password)
{
  node->password = password;
}

// goal: sets the next credential in a list of credentials
// param node: pointer to Cred struct to change successor of
// param next: pointer to new successor credential
//
// TODO: complete the function
void set_next(struct Cred* node, struct Cred* next)
{
  node->next = next;
}
