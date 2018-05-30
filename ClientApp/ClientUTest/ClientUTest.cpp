// ClientUTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <gtest\gtest.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::string line;
	std::getline(std::cin, line);
	return 0;
}
