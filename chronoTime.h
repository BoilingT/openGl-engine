#pragma once
#include <chrono>

class chronoTime
{
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point endTime;

public:

	void start() {
		startTime = std::chrono::steady_clock::now();
	}

	void end() {
		endTime = std::chrono::steady_clock::now();
	}

	long long getDifference() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	}
};

