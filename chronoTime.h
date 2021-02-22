#pragma once
#include <chrono>

class chronoTime
{
public:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point endTime;

	void setTimeStart() {
		startTime = std::chrono::steady_clock::now();
	}

	void setTimeStart(std::chrono::steady_clock::time_point time) {
		startTime = time;
	}

	void setTimeEnd() {
		endTime = std::chrono::steady_clock::now();
	}

	void setTimeEnd(std::chrono::steady_clock::time_point time) {
		endTime = time;
	}

	double deltaTime() {
		return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
};

