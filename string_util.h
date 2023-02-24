#pragma once
#include <vector>
#include <string>

using namespace std;

class string_util
{
public:
	static vector<string> split(string str, string reg = " ");
	static vector<string> iterate(string str, string reg);
	static vector<unsigned int> split_digits(string str);
	static void parse_int(const char* str, int& out);
	static void parse_float(const char* str, float& out);
	static void parse_double(const char* str, double& out);
	static void parse_bool(const char* str, bool& out);
	static void parse_lint(const char* str, long long int& out);
	static bool check_file_format(string file, string format);
	static bool match(string str, string reg);
	static string replace(string str, string what, string with);
};

