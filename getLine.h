#ifndef	GET_LINE_H
#define	GET_LINE_H
#include "lineParser.h"
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>

void getLine(std::string commandFile );
bool commandCheck(std::string commands);


#endif
