#pragma once
class csv_config
{
public:
	csv_config(char delim = ';', char row_delim = '\n', char escape = '"');

	csv_config& operator=(csv_config config);

	char delim, row_delim, escape;
};

