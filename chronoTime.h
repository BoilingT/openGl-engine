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

	double deltaTime() {
		return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
};

