#include "pomodoro.h"

Pomodoro::Pomodoro(int8_t focusDuration, int8_t shortBreakDuration, int8_t longBreakDuration)
	: Timer(focusDuration), FocusDuration(focusDuration), ShortBreakDuration(shortBreakDuration),
	LongBreakDuration(longBreakDuration), SetsCount(0) {
}


void Pomodoro::start() {
	std::cout << "\n--- Starting Pomodoro Session " << (SetsCount + 1) << " ---\n";
	runSession(FocusDuration, "Focus");
	SetsCount++;
	if (SetsCount < 4) {
		startShortBreak();
	}
	else {
		startLongBreak();
		SetsCount = 0; 
	}

}
void Pomodoro::runSession(int8_t duration, std::string label) {
	isRunning = true;
	auto startTime = std::chrono::steady_clock::now();
	std::cout << label << " for " << static_cast<int>(duration) << " minutes.\n";
	while (isRunning) {
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(currentTime - startTime).count();
		if (elapsed >= duration) {
			isRunning = false;
		}
	}
	std::cout << label << " session completed!\n";
}

void Pomodoro::startShortBreak() {
	std::cout << "Starting short break for " << static_cast<int>(ShortBreakDuration) << " minutes.\n";
	runSession(ShortBreakDuration, "Short Break");
}

void Pomodoro::startLongBreak() {
	std::cout << "Starting long break for " << static_cast<int>(LongBreakDuration) << " minutes.\n";
	runSession(LongBreakDuration, "Long Break");
}