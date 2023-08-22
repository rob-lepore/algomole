#pragma once
#include "../am.h"
#include <iostream>
#include <chrono>
class am::utils::Logger
{
public:
	Logger(std::string activity);
	
	void log(std::string msg, std::string end = "\n");

	std::string vec3(glm::vec3 v);

	void startTimer();

	void logElapsedTime(std::string message);

private:
	std::string m_activity;
	std::chrono::steady_clock::time_point m_start, m_stop;

};

