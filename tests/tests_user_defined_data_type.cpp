//
// Created by Andrey Solovyev on 22.09.2024.
//

#include "gtest/gtest.h"
#include "../include/segment_tree.hpp"

struct Date final {
	int year_;
	int month_;
	int day_;
	Date() noexcept  :year_(0), month_(0), day_(0) {}
	Date(double d) noexcept :year_(0), month_(0), day_(int(d)) {}
	Date(int year, int month, int day) noexcept :year_(year), month_(month), day_(day) {}
};//!struct

bool operator<(const Date& lhs, const Date& rhs) noexcept {
	if (lhs.year_!=rhs.year_) return lhs.year_<rhs.year_;
	else if (lhs.month_!=rhs.month_) return lhs.month_<rhs.month_;
	else return lhs.day_<rhs.day_;
}
bool operator==(const Date& lhs, const Date& rhs) noexcept {
	return lhs.year_==rhs.year_ && lhs.month_==rhs.month_ && lhs.day_==rhs.day_;
}
bool operator!=(const Date& lhs, const Date& rhs) noexcept {
	return !(lhs==rhs);
}

Date operator+(const Date& lhs, const Date& rhs) noexcept {
	int days = (lhs.year_ + rhs.year_) * 365 + (lhs.month_ + rhs.month_) * 30 + lhs.day_ + rhs.day_;
	int new_year = days / 365;
	int new_month = (days - new_year * 365) / 30;
	int new_day = days - new_year * 365 - new_month * 30;

	return Date (new_year,new_month, new_day);
}

Date operator+=(const Date& lhs, const Date& rhs) noexcept {
	return lhs+rhs;
}

Date operator*(const Date& lhs, int mult) noexcept {
	int days = (lhs.year_*365 + lhs.month_*30 + lhs.day_) * mult;
	int new_year = days / 365;
	int new_month = (days - new_year * 365) / 30;
	int new_day = days - new_year * 365 - new_month * 30;

	return Date (new_year,new_month, new_day);
}
Date operator*=(const Date& lhs, int mult) noexcept {
	return lhs*mult;
}

static std::vector<Date> data{
		{0, 0, 1},
		{3, 3, 3},
		{2, 0, 1},
};

inline auto sum_lambda = [](const Date a, const Date b) noexcept { return a+b; };
inline auto max_lambda = [](const Date a, const Date b) noexcept { return a<b ? b : a; };
inline auto min_lambda = [](const Date a, const Date b) noexcept { return a<b ? a : b; };


TEST (user_type, sum){
	::containers::segment_tree stree(data, sum_lambda);
	Date const sum {5, 3, 5};
	auto res {stree.query(0, 2)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(sum, res.value());
}

TEST (user_type, max){
	::containers::segment_tree stree(data, max_lambda);
	Date const max {3, 3, 3};
	auto res {stree.query(0, 2)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(max, res.value());
}

TEST (user_type, min){
	::containers::segment_tree stree(data, min_lambda);
	Date const min {0, 0, 1};
	auto res {stree.query(0, 2)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(min, res.value());
}

TEST (user_type, update){
	::containers::segment_tree stree_sum(data, sum_lambda);
	::containers::segment_tree stree_max(data, max_lambda);
	::containers::segment_tree stree_min(data, min_lambda);

	Date const date_to_add {2, 2, 2};
	for (int i = 0; i != 2; ++i) {
		stree_sum.update(date_to_add, i);
		stree_max.update(date_to_add, i);
		stree_min.update(date_to_add, i);
	}

	Date const sum {6, 4, 5};
	auto res {stree_sum.query(0, 2)};
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(sum, res.value());

	Date const max {2, 2, 2};
	res = stree_max.query(0, 2);
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(max, res.value());

	Date const min {2, 0, 1};
	res  = stree_min.query(0, 2);
	ASSERT_TRUE(res.has_value());
	ASSERT_EQ(min, res.value());
}

