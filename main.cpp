#include <iostream>
#include "csv_parser.h"
#include <vector>
#include <tuple>
#include <string>
#include "csv_iterator.h"
#include "csv_parser_exception.h"
#include "csv_writer.h"
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

bool comp(const tuple<int, string, float>& first, const tuple<int, string, float>& second) {
	return get<2>(first) > get<2>(second);
}

int main()
{
	setlocale(LC_ALL, "ru");

	//csv_parser<string, float, float> csv("test.csv", 1);
	csv_writer output("out.csv", {"group", "name", "result"});
	csv_parser<int, string, float> csv("lop_test.csv");
	vector<tuple<int, string, float>> results;

	double start = clock();
	try {
		for (auto row : csv) {
			results.push_back(row);
		}
	} 
	catch (csv_parser_exception e) {
		cerr << e.what();
		return -1;
	}
	sort(results.begin(), results.end(), comp);
	output.open();
	for (const auto& row : results) {
		output << row;
	}
	double end = clock();
	cout << "Time taken: " << (end - start) / CLOCKS_PER_SEC << endl;

	return 0;
}
