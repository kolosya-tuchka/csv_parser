#pragma once
#include <string>

using namespace std;

class csv_parser_exception
{
public:
	csv_parser_exception(string info);

	string what();

protected:
	string info;
};

