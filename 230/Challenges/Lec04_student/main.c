#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main()
{
  build_tree();
  prep_print(get_banana());
  printf("%s\n", get_print_buf());
}
