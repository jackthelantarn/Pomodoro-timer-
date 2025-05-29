#include "pomodoro.h"
#include<Windows.h>
#pragma comment(lib, "winmm.lib")  
Pomodoro::Pomodoro(int8_t focusDuration, int8_t shortBreakDuration, int8_t longBreakDuration)
	:FocusDuration(focusDuration), ShortBreakDuration(shortBreakDuration),
	LongBreakDuration(longBreakDuration), SetsCount(0) {
}

//start fuction from base class Timer implemented here
void Pomodoro::start() {
	std::cout << "\n--- Starting Pomodoro Session " << (SetsCount + 1) << " ---\n";
	//run focus session
	runSession(FocusDuration, "Focus"); 
	PlaySound(TEXT("Digital alarm clock sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //play sound when focus session is completed
	//counts the number of sets completed
	SetsCount++;    
	//if less than 4 sets completed, start short break
	if (SetsCount < 4) { 
		startShortBreak();
		PlaySound(TEXT("Digital alarm clock sound.wav"), NULL, SND_FILENAME | SND_ASYNC);; //play sound when short break session is completed
	}
	//if 4 sets completed, start long break
	else {
		startLongBreak();	
		PlaySound(TEXT("Digital alarm clock sound.wav"), NULL, SND_FILENAME | SND_ASYNC);; //play sound when long break session is completed
		SetsCount = 0; 
	}

}
//stop function from base class Timer implemented here
void Pomodoro::stop() {
	isRunning = false;
	std::cout << "Pomodoro session stopped.\n";
}
//runsesson takes duration and label as parameters
void Pomodoro::runSession(int8_t duration, std::string label) {
	isRunning = true;
	auto startTime = std::chrono::steady_clock::now(); //curret time is stored in startTime variable
	std::cout << label << " for " << static_cast<int>(duration) << " minutes.\n";
	while (isRunning) { 
		auto currentTime = std::chrono::steady_clock::now(); // check new time in loop 
		auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(currentTime - startTime).count(); //subtract start time from current time to get duration of time
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