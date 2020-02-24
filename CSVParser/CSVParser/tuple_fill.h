#pragma once

#include <tuple>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "parser_error.h"

template<typename T> T from_string(const std::string& str, int N, int curr_row)
{
	std::stringstream ss;
	ss << str;
	T t;
	ss >> t;

	if (ss.fail()) {
		throw type_mismatch("Type mismatch, problems in position", N, curr_row);
	}

	return t;
}

template<> std::string from_string(const std::string& str, int N, int curr_row)
{
	return str;
}


template <typename Tuple, unsigned N, unsigned Size>
struct fillTuple {
	static void fill(Tuple& tuple, const std::vector<std::string>& vector, int curr_row) {
		try {
			std::get<N>(tuple) = from_string<typename std::tuple_element<N, Tuple>::type>(vector[N], N, curr_row);
			//Проверяем следующий шаг
			fillTuple<Tuple, N + 1, Size>::fill(tuple, vector, curr_row);
		}
		catch (type_mismatch & err) {
			throw err;
		}
	}
};

template <typename Tuple, unsigned N>
struct fillTuple<Tuple, N, N> {
	static void fill(Tuple& tuple, const std::vector<std::string>& vector, int curr_row) {
		std::get<N>(tuple) = from_string<typename std::tuple_element<N, Tuple>::type>(vector[N], N, curr_row);
	}
};

template <typename Tuple, unsigned N>
struct fillTuple<Tuple, N, 0> {
	static void fill(Tuple& tuple, const std::vector<std::string>& vector, int curr_row) {}
};

//Создание последовательности из данных CSV файла
template <typename...Argc>
void makeTuple(std::tuple<Argc...>& arg, std::vector<std::string>& vector_of_str, int curr_row) {
	fillTuple<std::tuple<Argc...>, 0, sizeof...(Argc) - 1>::fill(arg, vector_of_str, curr_row);
}