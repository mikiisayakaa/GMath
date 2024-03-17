#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace GMath {

	//must be called with TIME_END() in pairs
#define TIME_START(info) \
	{ \
	 auto start = std::chrono::steady_clock::now(); \
	 std::string infoStr = std::string(info);

#define TIME_END() \
	auto end = std::chrono::steady_clock::now(); \
	std::chrono::duration<double, std::milli> elapsed = end - start; \
	std::cout << infoStr << " " << "Elapsed time: " << elapsed.count() << std::endl; \
	} \

}