#include "string_util.h"
#include <regex>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<string> string_util::split(string str, string reg) {
	vector<string> result;

	regex r(reg);
	sregex_token_iterator iterator(str.begin(), str.end(), r, -1);

	sregex_token_iterator end;
	for (; iterator != end; ++iterator) {
		string word = *iterator;
		if (word.size() > 0) {
			result.push_back(*iterator);
		}
	}

	return result;
}

vector<string> string_util::iterate(string str, string reg)
{
	regex reg_ex(reg);
	vector<string> res{ sregex_token_iterator(cbegin(str), cend(str), reg_ex, 1), sregex_token_iterator() };
	return res;
}

vector<unsigned int> string_util::split_digits(string str)
{
	vector<unsigned int> result;

	for (auto c : str) {
		if (c >= '0' && c <= '9') {
			result.push_back(c - '0');
		}
	}
	return result;
}

void string_util::parse_int(const char* str, int& out)
{
	try {
		out = atoi(str);
	}
	catch (invalid_argument const& exception) {
		throw invalid_argument("Invalid data\n");
	}
}

void string_util::parse_float(const char* str, float& out)
{
	try {
		out = stof(str);
	}
	catch (invalid_argument const& exception) {
		throw invalid_argument("Invalid data\n");
	};
}

void string_util::parse_double(const char* str, double& out)
{
	try {
		out = stod(str);
	}
	catch (invalid_argument const& exception) {
		throw invalid_argument("Invalid data\n");
	};
}

void string_util::parse_bool(const char* str, bool& out)
{
	string temp = str;
	if (temp == "false" || temp == "False" || temp == "0" || temp == "") {
		out = false;
		return;
	}
	if (temp == "true" || temp == "True" || temp == "1") {
		out = true;
		return;
	}

	throw invalid_argument("Invalid data\n");
}

void string_util::parse_lint(const char* str, long long int& out)
{
	try {
		out = stoll(str);
	}
	catch (invalid_argument const& exception) {
		throw invalid_argument("Invalid data\n");
	};
}

bool string_util::check_file_format(string file, string format)
{
	if (file.size() < format.size() + 1) {
		return false;
	}

	string _format = file.substr(file.size() - format.size(), format.size());
	return _format == format;
}

bool string_util::match(string str, string reg)
{
	regex r(reg);
	return regex_match(str, r);
}

string string_util::replace(string str, string what, string with)
{
	return regex_replace(str, regex(what), with);
}
