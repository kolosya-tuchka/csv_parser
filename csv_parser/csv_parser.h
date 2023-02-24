#pragma once
#include <tuple>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "string_util.h"
#include "csv_reader.h"
#include "csv_parser_exception.h"
#include <sstream>

using namespace std;

template <typename ...Args>
class csv_parser
{
public:
	template <Args...>
	csv_parser() {
		file.set_file_path("test.csv");
	}

	template <Args...>
	csv_parser(string file_path, unsigned int offset = 0, csv_config config = csv_config(';', '\n', '"')) : file(file_path, config) {
		this->offset = offset;
	}

	const tuple<Args...>& get_row() {
		return row;
	}

	void open() {
		file.open();
		make_offset();
	}

	void close() {
		file.close();
	}

	void next() {
		++row_index;
		vector<string> cols;
		file >> cols;
		int column = 0;
		try {
			parse(cols, column, row);
		}
		catch (invalid_argument e) {
			cerr << e.what();
			throw csv_parser_exception("Error in " + to_string(column + 1) + " column, " + to_string(row_index) + " row\n");
		}
	}

	operator bool() {
		return file;
	}

private:
	void make_offset() {
		vector<string> temp;
		for (row_index = 0; row_index < offset; ++row_index) {
			if (!*this) {
				break;
			}
			file >> temp;
		}
	}

	void parse(vector<string> args, int& count, tuple<>& row) {
		if (count != args.size()) {
			throw invalid_argument("Invalid count of arguments\n");
		}
	}

	template <typename ...Args>
	void parse(vector<string> args, int count, tuple<Args...>& row) {
		if (count == args.size()) {
			throw invalid_argument("Invalid count of arguments\n");
		}
		try {
			stringstream sstream(ios_base::in | ios_base::out);
			sstream << args[count++];
			try {
				sstream >> row._Myfirst._Val;
			}
			catch (invalid_argument e) {
				throw invalid_argument("Invalid argument\n");
			}
			parse(args, count, row._Get_rest());
		}
		catch (invalid_argument e) {
			throw invalid_argument(e.what());
		}
	}

	int row_index = 0;
	unsigned int offset = 0;
	tuple<Args...> row;
	csv_reader file;
};

stringstream& operator>>(stringstream& is, int& res) {
	string temp;
	is >> temp;
	string_util::parse_int(temp.c_str(), res);
	return is;
}

stringstream& operator>>(stringstream& is, long long& res) {
	string temp;
	is >> temp;
	string_util::parse_lint(temp.c_str(), res);
	return is;
}

stringstream& operator>>(stringstream& is, float& res) {
	string temp;
	is >> temp;
	string_util::parse_float(temp.c_str(), res);
	return is;
}

stringstream& operator>>(stringstream& is, double& res) {
	string temp;
	is >> temp;
	string_util::parse_double(temp.c_str(), res);
	return is;
}

stringstream& operator>>(stringstream& is, bool& res) {
	string temp;
	is >> temp;
	string_util::parse_bool(temp.c_str(), res);
	return is;
}

istream& operator>>(istream& is, tuple<>& args) {
	return is;
}

template <typename ...Args>
istream& operator>>(istream& is, tuple<Args...>& args) {
	is >> args._Myfirst._Val;
	return is >> args._Get_rest();
}

ostream& operator<<(ostream& os, tuple<> const& args) {
	return os;
}

template <typename ...Args>
ostream& operator<<(ostream& os, tuple<Args...> const& args) {
	os << args._Myfirst._Val << " ";
	return os << args._Get_rest();
}