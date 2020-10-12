#include <stdio.h>

#ifndef CH_HEAD
#define CH_HEAD

// Struct representing military time
// TODO: complete the struct
struct Time
{
    int hour;
    int min;
    int sec;
};

// Creates a Time struct given the hour, minute, and second
//   param hour: int representing the hour 0-23
//   param min: int representing the minute 0-59
//   param sec: int representing the second 0-59
//   return: a Time struct for the time representing the same time as the integers
struct Time create_time(int hour, int min, int sec);

// Gets the hour from a Time struct
//   param t: struct representing a time
//   return: an int representing the hour of time t
int get_hour(struct Time t);

// Gets the minute from a Time struct
//   param t: struct representing a time
//   return: an int representing the minute of time t
int get_min(struct Time t);

// Gets the second from a Time struct
//   param t: struct representing a time
//   return: an int representing the second of time t
int get_sec(struct Time t);

void set_hour(struct Time* t, int hour);
void set_min(struct Time* t, int min);
void set_sec(struct Time* t, int sec);

// Creates a Time struct representing the difference between two times
//   param t1: Time struct representing the beginning of interval
//   param t3: Time struct representing the end of interval
//   return: Time struct representing time between t1 and t2
struct Time elapsed_time(struct Time t1, struct Time t2);

#endif
