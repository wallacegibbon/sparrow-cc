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

using CmdArgMap = std::unordered_map<std::string, CmdArgument>;

CmdArgMap parse_cmd_arguments(int argc, const char **argv);

enum class CmdArgParseResult {
	MORE,
	FINISHED,
	ERROR_MISSING_VALUE,
	ERROR_UNKNOWN_OPTION
};

CmdArgParseResult parse_one_cmd_argument(
	int &argc,
	const char **&argv,
	CmdArgMap &result
);

void print_cmd_arguments(CmdArgMap &cmd_arguments);


} // namespace sparrow::cmd

