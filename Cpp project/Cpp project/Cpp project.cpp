// Cpp project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "pomodoro.h"
#include "DistractionFreePomodoro.h"

using namespace std;

int main()
{
	std::string focusDuration;
	std::string shortBreakDuration;
	std::string longBreakDuration;
	//asking user for input for timer durations
	std::cout << "Welcome to the Pomodoro Timer!\n";

	std::cout << "Enter your focus duration:\n";
	std::getline(std::cin, focusDuration);

	std::cout << "Enter your short break duration:\n";
	std::getline(std::cin, shortBreakDuration);

	std::cout << "Enter your long break duration:\n";
	std::getline(std::cin, longBreakDuration);

	
	//List of distracting apps
	std::vector<std::string> apps = { "WhatsApp.exe", "steam.exe" };
	// 25 min focus, 5 min short break, 15 min long break
	DistractionFreePomodoro pomodoro(stoi(focusDuration),stoi(shortBreakDuration),stoi(longBreakDuration),apps);
	char choice;
	//asking user if they want to start another session
	do {

		pomodoro.start();
		std::cout << "Do you want to start another session? (y/n): ";
		std::cin >> choice;
		if (choice	 != 'y' && choice != 'Y') {
			break;
		}
	} while (choice == 'y' || choice == 'Y');
	std::cout << "Thank you for using the Pomodoro Timer!\n";
	
}

