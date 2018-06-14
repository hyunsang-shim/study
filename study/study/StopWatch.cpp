#include "stdafx.h"
#include "StopWatch.h"
#include <ctime>


StopWatch::StopWatch()
{	
	startTime = clock();
}


StopWatch::~StopWatch()
{
}

void StopWatch::start()
{
	startTime = clock();
}

void StopWatch::stop()
{
	endTime = clock();
}

double StopWatch::getElapsedTime()
{
	return endTime - startTime;
}

double StopWatch::getStartTime()
{
	return startTime;
}

double StopWatch::getEndTime()
{
	return endTime;
}