#include <iostream>
#include <chrono>
class Timer  // abstract base class
{
protected: 
	int16_t duration;
	bool isRunning;

public:   
	Timer(int16_t duration	) : 
		duration(duration) {}

	virtual ~Timer() {
		std::cout << "Timer destroyed.\n";
	}

	virtual void start() = 0;

	int16_t getDuration() const { return duration; }
	void setDuration(int16_t newDuration) { duration = newDuration; }
	bool isTimerRunning() const { return isRunning; }
	
};


