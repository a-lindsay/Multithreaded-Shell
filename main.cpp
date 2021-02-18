#include <string>
#include <vector>
#include "getLine.h"
#include "lineParser.h"

void doInteractive() {
    std::string interactiveCommand;
    std::cerr << ">>";
    while (std::getline(std::cin, interactiveCommand)) {

        if (interactiveCommand.compare("quit") == 0)
            break;

        lineParser(interactiveCommand);
	std::cout << ">>";
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1){
        doInteractive();
    } else {
        getLine(argv[1]);
    }

    return 0;
}

