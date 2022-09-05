#include "command_line_args.h"
#include <iostream>
#include <cstring>

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

void print_cmd_arguments(CmdArgMap &cmd_arguments) {
	std::cout << "The command line arguments:" << std::endl << "\t";
	for (auto &kv : cmd_arguments)
		std::cout << kv.second.stringify();

	std::cout << std::endl;
}

CmdArgMap parse_cmd_arguments(int argc, const char **argv) {
	CmdArgMap result;
	CmdArgParseResult status = CmdArgParseResult::MORE;
	while (status == CmdArgParseResult::MORE)
		status = parse_one_cmd_argument(argc, argv, result);

	switch (status) {
	case CmdArgParseResult::ERROR_UNKNOWN_OPTION:
		std::cerr << "Unknown argument: " << *argv << std::endl;
		break;
	case CmdArgParseResult::ERROR_MISSING_VALUE:
		std::cerr << "Missing value for option: \""
			<< *argv << "\"" << std::endl;
		break;
	}

	return result;
}

inline void forward_argument_cursor(
	int &argc,
	const char **&argv,
	int step = 1
) {
	argc -= step;
	argv += step;
}

CmdArgParseResult parse_one_cmd_argument(
	int &argc,
	const char **&argv,
	CmdArgMap &result
) {
	if (argc == 0)
		return CmdArgParseResult::FINISHED;

	if (strcmp(*argv, "-v") == 0) {
		result.emplace("version", CmdArgument("-v", true));
		forward_argument_cursor(argc, argv);
	} else if (strcmp(*argv, "-g") == 0) {
		result.emplace("debug-info", CmdArgument("-g", true));
		forward_argument_cursor(argc, argv);
	} else if (strcmp(*argv, "-o") == 0) {
		if (argc <= 1)
			return CmdArgParseResult::ERROR_MISSING_VALUE;
		result.emplace("output", CmdArgument("-o", *(argv + 1)));
		forward_argument_cursor(argc, argv, 2);
	} else {
		return CmdArgParseResult::ERROR_UNKNOWN_OPTION;
	}

	return CmdArgParseResult::MORE;
}


} // namespace sparrow::cmd

