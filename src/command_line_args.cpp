#include "command_line_args.h"
#include <iostream>

namespace sparrow::cmd {

/// For example, bool argument is stringified like "-v" or ""(empty string),
/// while string argument is stringified like "-o output.o".
std::string CmdArgument::stringify() {
	std::string result = name_;

	if (type() == StrOrBool::STR)
		return result + " " + value().s + " ";

	if (type() == StrOrBool::BOOL && !value().b)
		return "";
	else
		return result + " ";
}

std::unordered_map<const char *, CmdArgument> cmd_arguments = {
	{ "verbose", CmdArgument("-v", true) },
	{ "debug-info", CmdArgument("-g", false) },
	{ "output", CmdArgument("-o", "blah.o") },
};

void print_cmd_arguments() {
	std::cout << "The command line arguments:" << std::endl << "\t";

	for (auto &kv : cmd_arguments)
		std::cout << kv.second.stringify();

	std::cout << std::endl;
}


} // namespace sparrow::cmd

