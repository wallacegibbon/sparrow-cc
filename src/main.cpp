#include "command_line_args.h"
#include "util.h"

int main(int argc, const char **argv) {
	if (argc == 1)
		sparrow::exit_info("Usage: sparrow [SOURCE FILE]", 0);

	sparrow::print_cmd_arguments();

	return 0;
}

