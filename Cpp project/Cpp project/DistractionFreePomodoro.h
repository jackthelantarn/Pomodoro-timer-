
#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "pomodoro.h"
#include "WebsiteBlocker.h"
class DistractionFreePomodoro : public Pomodoro {
private:
	//takes list of distracting apps as input 
	std::vector<std::string> blockedApps;
	bool isActive;

	WebsiteBlocker websiteBlocker;
	std::set<std::string> websitesToBlock = {
		"www.youtube.com",
		"www.instagram.com",
		"twitter.com",
		"facebook.com"
	};

	bool IsAppRunning(const std::string& appName);

public:
	//Constructor with default pomodoro timer value
	DistractionFreePomodoro(int8_t focusDuration = 25, int8_t shortBreakDuration = 5, int8_t longBreakDuration = 15,
		const std::vector<std::string>& appstoBlock = {});

	~DistractionFreePomodoro() = default;

	void runSession(int8_t duration, std::string label) override;
};
