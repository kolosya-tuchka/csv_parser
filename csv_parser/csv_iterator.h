#pragma once
#include <iterator>
#include <tuple>
#include <iostream>
#include <utility>
#include <fstream>
#include "csv_parser.h"

template <typename ...Args>
class csv_iterator {
public:
	using iterator_category = input_iterator_tag;
	
	using iterator = csv_iterator<Args...>;
	using value_type = tuple<Args...>;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using reference = const value_type&;

	csv_parser<Args...>* csv;

	csv_iterator(csv_parser<Args...>* csv) {
		this->csv = csv;
	}
	csv_iterator(const iterator&) = default;
	iterator& operator=(const iterator&) = default;
	~csv_iterator() = default;

	friend bool operator==(iterator left, iterator right) {
		return left.csv == right.csv;
	}

	friend bool operator!=(iterator left, iterator right) {
		return !(left == right);
	}

	reference operator*() const {
		return csv->get_row();
	}

	pointer operator->() const {
		return addressof(**this);
	}

	iterator& operator++() {
		if (!*csv) {
			csv->close();
			csv = nullptr;
		}
		else {
			csv->next();
		}
		return *this;
	}
};

template <typename ...Args>
csv_iterator<Args...> begin(csv_parser<Args...>& csv) {
	csv.open();
	csv_iterator<Args...> it{ &csv };
	return ++it;
}

template <typename ...Args>
csv_iterator<Args...> end(csv_parser<Args...>& csv) {
	return { nullptr };
}