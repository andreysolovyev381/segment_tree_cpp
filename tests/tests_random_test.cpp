//
// Created by Andrey Solovyev on 22.09.2024.
//

#include "gtest/gtest.h"
#include "../include/segment_tree.hpp"

#include <string>
#include <filesystem>
#include <fstream>

/**
 * @dev
 * this test was taken from LeetCode:
 * 307 Range Sum Query - Mutable
 * https://leetcode.com/problems/range-sum-query-mutable/description/?envType=problem-list-v2&envId=segment-tree
 * */

inline auto sum_lambda = [](const int a, const int b) noexcept{return a + b;};

inline auto initial_data = [](){
	std::vector<int> res;
	std::filesystem::path const initial_data_file
		{std::filesystem::path (CMAKE_SOURCE_DIR) / "tests/input_initial_values.txt"};
	std::fstream f (initial_data_file, std::ios::in);
	if (!f) {
		std::fprintf(stderr, "Haven't been able to open an initial data file %s\n", initial_data_file.c_str());
		return res;
	}
	int curr;
	while (f >> curr) res.push_back(curr);
	return res;
}();

inline auto input_actions = [](){
	std::vector<std::string> res;
	std::filesystem::path const input_actions_file
			{std::filesystem::path (CMAKE_SOURCE_DIR) / "tests/input_actions.txt"};
	std::fstream f (input_actions_file, std::ios::in);
	if (!f) {
		std::fprintf(stderr, "Haven't been able to open an input actions file %s\n", input_actions_file.c_str());
		return res;
	}
	std::string action;
	while (f >> action) res.push_back(action);
	return res;
}();

inline auto input_values = [](){
	std::vector<std::pair<int, int>> res;
	std::filesystem::path const input_values_file
			{std::filesystem::path (CMAKE_SOURCE_DIR) / "tests/input_values.txt"};
	std::fstream f (input_values_file, std::ios::in);
	if (!f) {
		std::fprintf(stderr, "Haven't been able to open an input values file %s\n", input_values_file.c_str());
		return res;
	}
	int first, second;
	while ((f >> first) && (f >> second)) res.emplace_back(first, second);
	return res;
}();

inline auto output_values = [](){
	std::vector<int> res;
	std::filesystem::path const output_values_file
			{std::filesystem::path (CMAKE_SOURCE_DIR) / "tests/output_expected_values.txt"};
	std::fstream f (output_values_file, std::ios::in);
	if (!f) {
		std::fprintf(stderr, "Haven't been able to open an output expected values file %s\n", output_values_file.c_str());
		return res;
	}
	int curr;
	while (f >> curr) res.emplace_back(curr);
	return res;
}();

TEST(big_test, sum) {
	// 24673 - it is a size of input data
	// 24672 - it is a max value of idx, checked
	ASSERT_EQ(input_actions.size(), input_values.size());
	::containers::segment_tree stree(initial_data, sum_lambda);
	std::size_t sz {input_actions.size()};
	std::vector<int> actual_res;
	actual_res.reserve(sz);
	for (std::size_t i = 0; i != sz; ++i) {
		if (input_actions[i] == "update") {
			stree.update(input_values[i].second, input_values[i].first);
		}
		else if (input_actions[i] == "sumRange") {
			auto const res {stree.query(input_values[i].first, input_values[i].second)};
			ASSERT_TRUE(res.has_value());
			actual_res.push_back(res.value());
		}
		else {
			ASSERT_FALSE(true) << "Unexpected input action" << input_actions[i] << '\n';
		}
	}

	ASSERT_EQ(actual_res.size(), output_values.size());
	sz = actual_res.size();
	for (std::size_t i = 0; i != sz; ++i){
		ASSERT_EQ(actual_res[i], output_values[i]);
	}
}
