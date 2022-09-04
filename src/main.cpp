#include "command_line_args.h"
#include "util.h"

using namespace sparrow;

int main(int argc, const char **argv) {
	if (argc == 1)
		exit_info("Usage: sparrow [SOURCE FILE]", 0);

	std::unordered_map<const char *, cmd::CmdArgument> cmd_args =
		cmd::parse_cmd_arguments(argc - 1, argv + 1);

	cmd::print_cmd_arguments(cmd_args);

	return 0;
}

