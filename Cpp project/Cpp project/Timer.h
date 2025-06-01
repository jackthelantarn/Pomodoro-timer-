
#ifndef TIMER_H
#define TIMER_H
#pragma once
#include <iostream>
#include <chrono>
class Timer  // abstract base class
{
protected: 
	bool isRunning;

public:   
	Timer() : isRunning(false) {
		std::cout << "Timer created.\n";
	}
	virtual ~Timer() {
		std::cout << "Timer destroyed.\n";
	}
	//virtual fuctions
	virtual void start() = 0;
	virtual void stop() = 0;

	bool isTimerRunning() const { return isRunning; }
	
};
#endif // TIMER_H

