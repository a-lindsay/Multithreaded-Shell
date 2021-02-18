#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "lineParser.h"
#include "excessParser.h"

void lineParser(std::string inputLine){
    excessParser ep;
    std::vector<std::string> splitCommands;
    std::stringstream ss(inputLine);

    if (inputLine.empty()) {
        return;
    }

    //splits by ;
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ';');
        splitCommands.push_back(substr);
    }

    for (size_t i = 0; i < splitCommands.size(); i++){
        if (splitCommands.at(i) == ""){
            splitCommands.erase(splitCommands.begin() + i);
        }
        ep.doStrip(splitCommands[i]);
        splitCommands[i] = ep.getParsedString();
    }

    runPrograms(splitCommands);

}
