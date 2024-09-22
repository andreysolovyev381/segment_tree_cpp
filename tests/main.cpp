//
// Created by Andrey Solovyev on 22.09.2024.
//

#include "gtest/gtest.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
	testing::InitGoogleTest(&argc, argv);
	testing::GTEST_FLAG(color) = "yes";
	auto res {RUN_ALL_TESTS()};
	return res;
}

//todo

