#include "excessParser.h"

excessParser::excessParser() : result("") { }

excessParser::~excessParser() { }

void excessParser::doStrip(std::string line) {
	std::string temp;

	temp = stripComments(line);
	temp = tabToSpace(temp);
	temp = stripOuter(temp);
	temp = stripInner(temp);

	result = temp;
}

std::string excessParser::getParsedString() {
	return result;
}

std::string excessParser::stripComments(std::string line) {
	/* Determine whether or not there are any comments to strip.
	 * This means getting the index of the first # found. However,
	 * it must be determined that # is not part of a quote or string
	 * literal.
	 */

	bool found_comment = false;
	bool in_quote = false;
	bool in_literal = false;
	size_t i;

	for (i = 0; i < line.size(); ++i) {
		if (line[i] == '\"' && !in_literal) {
			in_quote = !in_quote;
		} else if (line[i] == '\'' && !in_quote) {
			in_literal = !in_literal;
		} else if (line[i] == '#' && !in_literal && !in_quote) {
			found_comment = true;
			break;
		}
	}

	if (!found_comment) {
		return line;
	}

	std::string stripped;

	stripped = line.substr(0,i);

	return stripped;
}

std::string excessParser::tabToSpace(std::string line) {
	for (size_t i = 0; i < line.size(); ++i) {
		if (line[i] == '\t') {
			line.replace(i, 1, 1, ' ');
		}	
	}
	return line;
}

std::string excessParser::stripOuter(std::string line) {
	while (line[0] == ' ') {
		line.erase(0,1);
	}

	while (line[line.size() - 1] == ' ') {
		line.erase(line.size() - 1, 1);
	}

	return line;
}

std::string excessParser::stripInner(std::string line) {
	bool found_whitespace = false;

	for (size_t i = 0; i < line.size(); ++i) {
		/* If we found the first whitespace between words,
		 * then set the bool. We'll ignore the first one
		 */
		if (!found_whitespace && line[i] == ' ') {
			found_whitespace = true;
		} else if (found_whitespace && line[i] == ' ') {
			line.erase(i, 1);
		} else if (line[i] != ' '){
			found_whitespace = false;
		}
	}
	return line;
}
