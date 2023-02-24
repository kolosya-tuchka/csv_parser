#pragma once
#include <string>
#include "csv_config.h"
#include <fstream>
#include <vector>

using namespace std;

class csv_reader
{
public:
	csv_reader();
	csv_reader(string file_path, csv_config config = csv_config(';', '\n', '"'));
	~csv_reader();

	void set_file_path(string file_path);
	string get_file_path();
	
	void open();
	void open(string file_path);
	void close();

	operator bool();
	void operator>>(vector<string>& out);

private:
	void operator>>(char& out);

	static const int buf_size = 100000;
	int cur_buf_size = 0;
	int cur_byte = 0;
	char buffer[buf_size];

	string file_path;
	ifstream input;
	csv_config config;

	void load_buffer();
	vector<string> read_row();
};