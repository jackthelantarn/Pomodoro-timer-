
#include "DistractionFreePomodoro.h"
#include<Windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
//User defined constructor for DistractionFreePomodoro class
DistractionFreePomodoro::DistractionFreePomodoro(int8_t focusDuration, int8_t shortBreakDuration, int8_t longBreakDuration,
	const std::vector<std::string>& appstoBlock)
	: Pomodoro(focusDuration, shortBreakDuration, longBreakDuration), blockedApps(appstoBlock), isActive(false) {
}
//Default value for pomodoro timer
DistractionFreePomodoro::DistractionFreePomodoro(int8_t focusDuration=25, int8_t shortBreakDuration=5, int8_t longBreakDuration=15,
	const std::vector<std::string>& appstoBlock)
	: Pomodoro(focusDuration, shortBreakDuration, longBreakDuration), blockedApps(appstoBlock), isActive(false) {
}

bool DistractionFreePomodoro::IsAppRunning(const std::string& appName) {
	//get the list of running apps in a text file
	system("tasklist > tasks.txt");

	std::ifstream file("tasks.txt");
	std::string line;
	// Check if given app is running by searching in the file
	while (std::getline(file, line)) {
		if (line.find(appName) != std::string::npos) {
			file.close();
			return true; // App is running
		}
	}
	file.close();
	return false; // App is not running
}

void DistractionFreePomodoro::runSession(int8_t duration, std::string label) {
	isRunning = true;
	auto startTime = std::chrono::steady_clock::now();
	std::cout << label << " for " << static_cast<int>(duration) << " minutes.\n";
	//Initiare WebsiteBlocking when focus session starts
	if (label == "Focus") {
		std::cout << "[System] Blocking websites...\n";
		for (const auto& site : websitesToBlock) {
			websiteBlocker.blockWebsite(site);
		}
	}
	//Unblock websites when short or long break starts
	else {
		std::cout << "[System] Unblocking websites...\n";
		for (const auto& site : websitesToBlock) {
			websiteBlocker.unblockWebsite(site);
			std::cout << "[System] " << site << " has been unblocked.\n";
		}
		std::cout << "[System] Websites unblocked.\n";
	}
	//Innitiate app blocking 
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::seconds(5)); // check every 5sec if blcoked app is found running
		//if distracting application is running then terminate it
		if(label == "Focus"){ 
			for (const auto& app : blockedApps) {
				if (IsAppRunning(app)) {
					std::cout <<"Blocked app detected: " << app <<" Terminating...\n";
					std::string command = "taskkill /IM " + app + " /F >nul 2>&1";
					system(command.c_str());
					std::cout << app << " has been terminated.\n";
					//Messebox to notify user that distracting app is detected
					MessageBox(NULL, TEXT("Please stay focus on your work!"), TEXT("DISTRACTING APP DETECTED!"), MB_OK | MB_ICONINFORMATION);
				}
			}
		}
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(currentTime - startTime).count();
		if (elapsed >= duration) {
			isRunning = false;
		}
	}

	std::remove("tasks.txt");
	std::cout << label << " session completed!\n";
}
