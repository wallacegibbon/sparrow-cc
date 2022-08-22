#pragma once

#include <unordered_map>
#include <string>

namespace sparrow {

class ArgumentPair {
	/// for simplicity, only `string` and `bool` arguments are supported.
	enum class ValueType { BOOL, STR };

public:
	ArgumentPair(const char *name, bool value)
		: name_(name), type_(ValueType::BOOL), bvalue_(value) {}

	ArgumentPair(const char *name, const char *value)
		: name_(name), svalue_(value) {}

	std::string stringify();

private:
	const char *name_;
	ValueType type_ = ValueType::STR;
	const char *svalue_ = nullptr;
	const bool bvalue_ = false;
};

/// A global variable for holding command line arguments
extern std::unordered_map<const char *, ArgumentPair> cmd_arguments;

/// the parsed result is stored in global variable `sparrow::cmd_arguments`.
bool parse_arguments(const int argc, const char **argv);

void print_cmd_arguments();


} // namespace sparrow

