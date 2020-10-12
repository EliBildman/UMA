# Overview

This project will give you experience writing a simple C++ program and
submitting to the autograder. For this assignment, you will write a
program in C++ that generates an "inverted index" of all the words in
a list of text files. (See http://en.wikipedia.org/wiki/Inverted_index
for more details.) The goal of this assignment is to ensure that you
are sufficiently up to speed in C++ to handle the rest of the
course. We will also use this program in subsequent assignments.

## Input

Your inverter will take exactly one argument: a file that contains a
list of filenames.  Each filename will appear on a separate line.

Each of the files described in the first file will contain text that
you will build your index from. For example:

### inputs.txt

```
foo1.txt
foo2.txt
```

### foo1.txt

```
this is a test. cool.
```

### foo2.txt

```
this is also a test.
boring.
```

## Output

Your inverter should output to a string all of the words from all of
the inputs, in "alphabetical" order, followed by the document numbers
in which they appear, in order. For example (note: your program must
produce exactly this output):

```
a: 0 1
also: 1
boring: 1
cool: 0
is: 0 1
test: 0 1
this: 0 1
```

Alphabetical is defined as the order according to ascii.  So "The" and
"the" are separate words, and "The" comes first.  Only certain words
should be indexed.  words are anything that is made up of only alpha
characters, and not numbers, spaces, etc.  "Th3e" is two words, "Th"
and "e".

Files are incrementally numbered, starting with 0.  Only valid,
openable files should be included in the count. (is_open comes in
handy here)

Your program should absolutely not produce any other output.
Extraneous output, or output formatted incorrectly (extra spaces etc.)
will make the autograder mark your solution as incorrect.  Please
leave yourself extra days to work these problems out.

# Implementation Hints

Implement the data structure using C++ Standard Template Library (STL)
as a map of sets, as in:

```c++
map<string, set<int> > invertedIndex;
```

Use C++ strings

```c++
#include <string>
```

and file streams:

```c++
#include <fstream>
```

Remember, your program needs to be robust to errors.  Files may be
empty, etc.  Please handle these cases gracefully and with no extra
output.

The noskipws operator may be useful in parsing the input:

```c++
input >> noskipws >> c;
```

# Debugging Help

It is important that you use the `gdb` debugger to debug your code
when you encounter problems. You can easily start the `gdb` debugger
from the command line:

```bash
$ gdb PROGRAM
```

Where `PROGRAM` is the program you compiled. You should look at the
provided `gdb` cheatsheet to see some of the commands you can
execute. If you need additional help you can take a look at [this
tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/).

You will inevitably encounter cases when your code fails a test or
worse, the test program exits with a segmentation violation
(segfault). To debug the code in a test requires you to understand how
the google test framework generates C++ code and how the C++ compiler
generates method signatures. In short, this is what you want to do:

```bash
$ gdb TEST_PROGRAM
(gdb) b TestSuite_TestName_Test::TestBody()
```

The `SuiteName` and `TestName` correspond to how you write a test
using the google test framework. In particular, this is the basic
structure of a test:

```C++
TEST(SuiteName, TestName) {
  // the test body
}
```

You should also know that the `b` (break) command provides tab
completion. So, you can type in the following:

```bash
(gdb) b TestSuite[TAB][TAB]
```

The `[TAB]` is hitting the `tab` key on your keyboard. You can hit it
twice in rapid succession to see all the possible completions.

# C++ Resources

This assignment touches on a variety of C++ language concepts and
libraries that are useful to understand before you get started. The
following links should help you in your work on this assignment. You
should take the time to review these resources before and during the
assignment to help you complete your work:

* [C++ Language Tutorials](http://www.cplusplus.com/doc/tutorial/)
* [Basic I/O](http://www.cplusplus.com/doc/tutorial/basic_io/)
* [Namespaces](http://www.cplusplus.com/doc/oldtutorial/namespaces/)
* [Strings](http://www.cplusplus.com/reference/string/string/)
* [Map](http://www.cplusplus.com/reference/map/map/)
* [Set](http://www.cplusplus.com/reference/set/set/)
* [Queue](http://www.cplusplus.com/reference/queue/queue/)

Again, spend some time studying up on these C++ basics. The best way
to do this is to write out the examples and compile them to see how
they work. Spending a little time to prepare will go a long way in
successfully implementing this assignment.