#include <stdio.h>
#include <string.h>

#ifndef CH_HEAD
#define CH_HEAD

// goal: copy nlines lines from rfile to wfile
// param rfile: name of file to read from
// param wfile: name of file to write to
// param nlines: number lines to copy
// return: error code
//   0 if no issues
//   -1 if error in opening or closing file
int copy(const char* rfile, const char* wfile, int nlines);

#endif