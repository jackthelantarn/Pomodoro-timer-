
#ifndef POMODORO_H
#define POMODORO_H
#pragma once
#include "timer.h"
#include <chrono>
#include <iostream>
class Pomodoro : public Timer
{
protected: 
	int8_t FocusDuration;
	int8_t ShortBreakDuration;
	int8_t LongBreakDuration;
	int8_t SetsCount;
public:
	Pomodoro(int8_t focusDuration, int8_t shortBreakDuration, int8_t longBreakDuration);

	~Pomodoro() {}

	void start() override; //virtual fuction from base class Timer
	void stop() override; //override stop function from base class Timer
	virtual void runSession(int8_t duration, std::string label) ;
	void startShortBreak();
	void startLongBreak();

	int8_t getFocusDuration() const { return FocusDuration; }
	int8_t getShortBreakDuration() const { return ShortBreakDuration; }
	int8_t getLongBreakDuration() const { return LongBreakDuration; }
	int8_t getSetsCount() const { return SetsCount; }
};
#endif // POMODORO_H

