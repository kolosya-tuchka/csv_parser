#include "csv_reader.h"
#include "string_util.h"

csv_reader::csv_reader()
{
	file_path = "test.csv";
	config = csv_config(';', '\n', '"');
}

csv_reader::csv_reader(string file_path, csv_config config)
{
	set_file_path(file_path);
	this->config = config;
}

csv_reader::~csv_reader()
{
	input.close();
}

void csv_reader::set_file_path(string file_path)
{
	if (input.is_open()) {
		return;
	}
	this->file_path = file_path;
}

string csv_reader::get_file_path()
{
	return file_path;
}

void csv_reader::open()
{
	input.open(file_path, ios_base::binary);
}

void csv_reader::open(string file_path)
{
	set_file_path(file_path);
	open();
}

void csv_reader::close()
{
	input.close();
}

csv_reader::operator bool()
{
	return (input.good()) || cur_buf_size > cur_byte;
}

void csv_reader::operator>>(vector<string>& out)
{
	out = read_row();
}

void csv_reader::operator>>(char& out)
{
	if (cur_byte >= cur_buf_size) {
		load_buffer();
	}
	out = buffer[cur_byte++];
}

void csv_reader::load_buffer()
{
	input.read(buffer, buf_size);
	cur_byte = 0;
	cur_buf_size = input.gcount();
}

vector<string> csv_reader::read_row()
{
	vector<string> result;

	bool escaping = false;
	char cur;
	char last = config.escape + 1;
	string temp;
	while (*this) {
		(*this) >> cur;
		if (cur == config.escape) {
			if (last == cur) {
				temp += cur;
			}
			last = cur;
			escaping = !escaping;
			continue;
		}
		if (escaping) {
			temp += cur;
			last = cur;
			continue;
		}

		if (cur == config.delim) {
			if (temp.size() > 1 && temp[temp.size() - 2] == config.escape && last == config.escape) {
				temp.erase(temp.begin() + (temp.size() - 2));
			}

			last = config.escape + 1;
			result.push_back(move(temp));
			continue;
		}
		if (cur == config.row_delim) {
			result.push_back(move(temp));
			return result;
		}

		temp += cur;
		last = cur;
	}
}
