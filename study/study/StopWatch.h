#pragma once

#include <ctime>
#include <cmath>

class StopWatch
{
public:
	StopWatch();
	~StopWatch();
	void start();
	void stop();
	double getElapsedTime();	
	double getStartTime();
	double getEndTime();

private:
	clock_t startTime;	
	clock_t endTime;
};

