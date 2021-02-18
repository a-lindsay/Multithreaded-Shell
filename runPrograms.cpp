#include "runPrograms.h"

/* provide the number of commands and the array of strings.
 * In addition, provide pointer to argc array.
 * This is needed for freeing memory.
 * The function returns char ***, which is an array of argv[]
 * arrays.
 */
char ***createArrayArgv(size_t com_num, 
	std::string commands[],
	size_t **argc) {
	
	std::stringstream cstream;
	std::string temp;
	
	char ***argv = new char**[com_num];
	
	memset(*argc, 0, com_num*sizeof(size_t));

	for (size_t i = 0; i < com_num; ++i) {
		cstream.str("");
		cstream.clear();
		
		cstream << commands[i];

		while (std::getline(cstream, temp, ' ')){
			(*argc[i])++;
		}
			
		cstream.clear();
		cstream.seekg(0, std::ios::beg);

		argv[i] = new char*[*argc[i]+1];
		argv[i][*argc[i]] = NULL;

		for (size_t j = 0; j < *argc[i]; ++j) {
			std::getline(cstream, temp, ' ');

			argv[i][j] = new char[temp.size()+1];
			memcpy(argv[i][j], temp.c_str(), temp.size());
			argv[i][j][temp.size()] = 0;
		}
		(*argc[i])++;
	}
	return argv;
}

/* Free the array of argv arrays. 
 * Char ***argv -> array of argv arrays
 * size_t com_num -> Number of commands
 * size_t argc *argc -> argc for each argv in array
 */
void freeArrayArgv(char ***argv, size_t com_num, size_t *argc) {
	for (size_t i = 0; i < com_num; ++i) {
		for (size_t j = 0; j < *argc; ++j){
			delete [] argv[i][j];
		}	
		delete [] argv[i];
	}
	delete [] argv;

}

void runPrograms(std::vector<std::string> commands) {
	// Convert vector to an array of strings
	std::string str_array[commands.size()];
	std::copy(commands.begin(), commands.end(), str_array);
	// Create argc array and pointer to it
	size_t argc[commands.size()];
	size_t *argc_ptr = &argc[0];

	// Convert array of strings to array of argv arrays
	char ***argv = createArrayArgv(commands.size(), str_array, &argc_ptr);
	pid_t result = 0;
	int e_result = 0;
	
	// Fork and exec each command
	for (size_t i = 0; i < commands.size(); ++i) {
		result = fork();

		if (result < 0) {
			std::cerr << "Fork error for command "
			<< commands[i]  << ": " << strerror(errno)
			<< std::endl;
			continue;
		}

		// If we're the child, go ahead and execute
		if (result == 0) {
			if ((e_result = execv(argv[i][0], argv[i])) < 0) {
				std::cerr << "Exec error for command "
				<< commands[i] << ": " << strerror(errno)
				<< std::endl;
			}
			freeArrayArgv(argv, commands.size(), argc_ptr);
			exit(e_result);

		}

		/* Since we're executing concurrently, we're going straight
		 * to the next command
		 */
	}

	// Free associated memory now that we're done
	freeArrayArgv(argv, commands.size(), argc_ptr);
}
