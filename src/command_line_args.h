#pragma once

#include <unordered_map>
#include <string>

namespace sparrow::cmd {

/// this is a tagged union for representing a bool/string in an efficient way.
class StrOrBool {
public:
	enum Type { BOOL, STR };
	union Value { const char *s; bool b; };

	StrOrBool(Type type, Value value) : type_(type), value_(value) {}

	StrOrBool(const char *value) :
		type_(STR), value_(Value{ .s = value }) {}

	StrOrBool(bool value) :
		type_(BOOL), value_(Value{ .b = value }) {}

public:
	Type type_ = Type::STR;
	Value value_ = { nullptr };
};

class CmdArgument {
public:
	CmdArgument(const char *name, bool value) :
		name_(name), value_(StrOrBool(value)) {}

	CmdArgument(const char *name, const char *value) :
		name_(name), value_(StrOrBool(value)) {}

	std::string stringify();

	StrOrBool::Type type() { return value_.type_; }
	StrOrBool::Value value() { return value_.value_; }

private:
	const char *name_;
	StrOrBool value_;
};

/// A global variable for holding command line arguments
extern std::unordered_map<const char *, CmdArgument> cmd_arguments;

/// the parsed result is stored in global variable `sparrow::cmd_arguments`.
bool parse_arguments(const int argc, const char **argv);

void print_cmd_arguments();


} // namespace sparrow::cmd

