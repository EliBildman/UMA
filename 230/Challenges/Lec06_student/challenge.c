#include "challenge.h"

// goal: copy nlines lines from rfile to wfile
// param rfile: name of file to read from
// param wfile: name of file to write to
// param nlines: number lines to copy
// return: error code
//   0 if no issues
//   -1 if error in opening or closing file
//
// TODO: complete the function
//   1. open files. do NOT open wfile in append mode (don't forget error checking)
//   2. copy the n lines (beware nline > number of lines in rfile)
//   3. close files
int copy(const char* rfile, const char* wfile, int nlines)
{
  FILE *fin;
  FILE *fout;
  if((fin = fopen(rfile, "r")) == NULL) return -1;
  if((fout = fopen(wfile, "w")) == NULL) return -1;

  int i = 0;
  while(i < nlines && !feof(fin)) {
    char c = getc(fin);
    if(c == '\n') i++;
    if(!feof(fin)) putc(c, fout);
  }
  
  fclose(fin);
  fclose(fout);

  return 0;
}
