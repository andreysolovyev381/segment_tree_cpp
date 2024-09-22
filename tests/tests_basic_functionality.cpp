//
// Created by Andrey Solovyev on 22.09.2024.
//

#include "gtest/gtest.h"
#include "../include/segment_tree.hpp"
#include <cmath>
#include <numeric>


static std::vector<int> data {9, 27, 81, -54, 9};
inline auto max_lambda = [](const int a, const int b) noexcept {return std::max(a, b);};
inline auto sum_lambda = [](const int a, const int b) noexcept{return a + b;};
inline auto min_lambda = [](const int a, const int b) noexcept {return std::min(a, b);};
inline auto gcd_lambda = [](const int a, const int b) noexcept {return std::gcd(a, b);};
inline auto lcm_lambda = [](const int a, const int b) noexcept{return std::lcm(a, b);};

TEST(funcs, max) {
	::containers::segment_tree stree(data, max_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(81, res.value());
}//!test

TEST(funcs, sum) {
	::containers::segment_tree stree(data, sum_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(72, res.value());
}//!test

TEST(funcs, min) {
	::containers::segment_tree stree (data, min_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(-54, res.value());
}//!test

TEST(funcs, gcd) {
	::containers::segment_tree stree (data, gcd_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(9, res.value());
}//!test

TEST(funcs, lcm) {
	::containers::segment_tree stree (data, lcm_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(162, res.value());
}//!test

TEST(funcs, sub_range) {
	::containers::segment_tree stree(data, max_lambda);
	//9, 27, 81, -54, 9
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(81, res.value());

	res  = stree.query(1, 2);
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(81, res.value());

	res  = stree.query(3, 4);
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(9, res.value());

	res  = stree.query(3, 3);
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(-54, res.value());

}//!test

TEST(build, ctor) {
	::containers::segment_tree stree (data, max_lambda);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(81, res.value());
}//!test

TEST(build, method) {
	::containers::segment_tree<int, decltype(max_lambda)> stree;
	stree.build(data);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(81, res.value());
}//!test

TEST(update, one_elem) {
	::containers::segment_tree stree(data, max_lambda);
	//9, 27, 81, -54, 9
	stree.update(100, 0);
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(100, res.value());
}//!test

TEST(update, many_elems) {
	::containers::segment_tree stree(data, max_lambda);
	//9, 27, 81, -54, 9
	for (int i = 0; i != 2; ++i) {
		stree.update(100 + i, i);
	}
	auto res {stree.query(0, 4)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(101, res.value());
}//!test
