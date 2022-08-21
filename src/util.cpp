#include "util.h"
#include <cstdlib>
#include <iostream>

namespace sparrow {

void exit_info(const char *info, int exit_code) {
	std::cout << info << std::endl;
	exit(exit_code);
}

}
