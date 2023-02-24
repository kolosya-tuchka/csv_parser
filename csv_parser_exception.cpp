#include "csv_parser_exception.h"

csv_parser_exception::csv_parser_exception(string info)
{
	this->info = info;
}

string csv_parser_exception::what()
{
	return info;
}
