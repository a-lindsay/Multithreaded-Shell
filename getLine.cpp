#include "getLine.h"



void getLine(std::string commandFile)
{
    std::ifstream inFile;
    std::string commands;
    std::string checkShebang;
    inFile.open(commandFile);
	
    // Get the shebang in order to check it
    getline(inFile, checkShebang);

    // Remove whitespace
    checkShebang.erase(std::remove_if(checkShebang.begin(),
    			checkShebang.end(),
			::isspace),
			checkShebang.end());
    // Remove the supposed #!
    checkShebang.erase(0, 1);
    checkShebang.erase(0, 1);
    
    if (access(checkShebang.c_str(), X_OK) < 0) {
    	std::cerr << "Failed to find shebang in " << checkShebang << std::endl;
	return;
    }

    while(getline(inFile, commands))
    {
        if(commandCheck(commands))
        {
            lineParser(commands);
        }
    }
    inFile.close();
}

bool commandCheck(std::string commands)
{
    for(size_t i = 0; i < commands.length(); i++)
    {
        if(!std::isspace(commands[i]))
        {
            if(commands[i] == '#')
            {
                return false;
            }
            
            return true;
        }
    }
    return false;
}

