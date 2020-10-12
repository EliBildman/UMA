#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main()
{
  struct Time t1 = create_time(1,2,3);
  struct Time t2 = create_time(4,1,6);
  struct Time dt = elapsed_time(t1, t2);
  printf("%d, %d, %d\n", dt.hour, dt.min, dt.sec);
}
