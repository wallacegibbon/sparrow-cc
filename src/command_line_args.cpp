#include "command_line_args.h"
#include <iostream>

namespace sparrow {

/// For example, bool argument is stringified like "-v" or ""(empty string),
/// while string argument is stringified like "-o output.o".
std::string ArgumentPair::stringify() {
	std::string result = name_;

	if (type_ == ValueType::STR)
		return result + " " + svalue_;

	if (type_ == ValueType::BOOL && !bvalue_)
		return "";
	else
		return result;
}

std::unordered_map<const char *, ArgumentPair> cmd_arguments = {
	{"v", sparrow::ArgumentPair("v", true)},
	{"g", sparrow::ArgumentPair("g", false)},
	{"o", sparrow::ArgumentPair("o", "blah.o")},
};

void print_cmd_arguments() {
	std::cout << "The command line arguments:" << std::endl << "\t";

	for (auto &kv : cmd_arguments)
		std::cout << kv.second.stringify() << ' ';

	std::cout << std::endl;
}


} // namespace sparrow

