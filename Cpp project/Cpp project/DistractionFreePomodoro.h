#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "pomodoro.h"

class DistractionFreePomodoro : public Pomodoro {
private:
	std::vector<std::string> blockedApps;
	bool isActive;

	bool IsAppRunning(const std::string& appName);

public:
	DistractionFreePomodoro(int8_t focusDuration, int8_t shortBreakDuration, int8_t longBreakDuration,
		const std::vector<std::string>& appstoBlock);

	~DistractionFreePomodoro() = default;

	void runSession(int8_t duration, std::string label) override;
};
