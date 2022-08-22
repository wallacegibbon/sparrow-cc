#include "command_line_args.h"
#include "util.h"

using namespace sparrow;

int main(int argc, const char **argv) {
	if (argc == 1)
		exit_info("Usage: sparrow [SOURCE FILE]", 0);

	cmd::print_cmd_arguments();

	return 0;
}

