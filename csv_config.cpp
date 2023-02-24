#include "csv_config.h"

csv_config::csv_config(char delim, char row_delim, char escape)
{
	this->delim = delim;
	this->row_delim = row_delim;
	this->escape = escape;
}

csv_config& csv_config::operator=(csv_config config)
{
	if (this == &config) {
		return *this;
	}

	delim = config.delim;
	row_delim = config.row_delim;
	escape = config.escape;

	return *this;
}
