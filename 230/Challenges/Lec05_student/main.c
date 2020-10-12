#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main()
{
  struct Cred *c = cred("c", "C", NULL);
  struct Cred *b = cred("b", "B", c);
  struct Cred *a = cred("a", "A", b);
  
  struct Cred *temp = a;
  while(temp != NULL) {
    printf("%s\n", get_username(temp));
    temp = temp->next;
  }

}
