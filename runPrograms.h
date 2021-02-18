#ifndef	RUN_PROGRAMS_H
#define	RUN_PROGRAMS_H
#include <string>
#include <cstring>
#include <cstddef>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

/* runPrograms expects a vector of strings as an argument. This vector represents
 * an array of commands
 *
 * It is expected that excess white space has been removed from the vector of 
 * strings. This includes tabs, leading, trailing, and extra spaces in between
 * words.
 *
 * The first thing runPrograms will do is convert the vector of strings into an
 * array of strings. 
 * From there,runPrograms will convert the array of strings into an array of argv 
 * arrays. commands -> **argv[]. After that, it will fork and exec, providing each
 * *argv[].
 */
void runPrograms(std::vector<std::string> commands);

#endif
