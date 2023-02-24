#pragma once
#include <string>
#include "csv_config.h"
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

class csv_writer
{
public:
	csv_writer();
	csv_writer(string file_path, vector<string> field_names = vector<string>(), csv_config config = csv_config(';', '\n', '"'));
	~csv_writer();

	void set_file_path(string file_path);
	string get_file_path();

	void open();
	void open(string file_path);
	void close();

	template <typename ...Args>
	void operator<<(const tuple<Args...>& in) {
		write_row(in);
	}

private:
	string file_path;
	ofstream output;
	csv_config config;
	vector<string> field_names;

	template <typename value_type> 
	void operator<<(value_type in) {
		output << config.escape << in << config.escape;
	}

	void operator<<(const vector<string>& in) {
		for (int i = 0; i < in.size(); ++i) {
			(*this) << in[i];
			if (i < in.size() - 1) {
				output << config.delim;
			}
		}
		output << config.row_delim;
	}

	void operator<<(string in) {
		output << config.escape;
		for (auto c : in) {
			output << c;
			if (c == config.escape) {
				output << config.escape;
			}
		}
		output << config.escape;
	}

	void write_row(tuple<> in) {
		output << config.row_delim;
	}

	template <typename ...Args>
	void write_row(tuple<Args...> in) {
		(*this) << in._Myfirst._Val;
		if (tuple_size<decltype(in)>::value != 1) {
			output << config.delim;
		}
		write_row(in._Get_rest());
	}
};

