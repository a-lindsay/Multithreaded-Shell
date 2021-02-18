#ifndef	EXCESS_PARSER_H
#define	EXCESS_PARSER_H
#include <sstream>
#include <string>

/* Parse and remove excess white space and comments */
class excessParser {
public:
	excessParser();
	~excessParser();
	void doStrip(std::string line);
	std::string getParsedString();
private:
	std::string stripComments(std::string);
	std::string tabToSpace(std::string);
	std::string stripOuter(std::string);
	std::string stripInner(std::string);

	std::string result;
};

#endif
