#include "Logger.h"

using namespace am::utils;

Logger::Logger(std::string activity) {
	m_activity = activity;
}

void Logger::log(std::string msg, std::string end) {
	std::cout << "[" << m_activity << "]  " << msg << end;
}

std::string Logger::vec3(glm::vec3 v) {
	return "(" + std::to_string(v.x) + " " + std::to_string(v.y) + " " + std::to_string(v.z) + ")";
}

void Logger::startTimer() {
	m_start = std::chrono::high_resolution_clock::now();
}

void Logger::logElapsedTime(std::string message) {
	m_stop = std::chrono::high_resolution_clock::now();
	log(message + " -> [ " + std::to_string((m_stop - m_start).count() / 1000000) + " ms ]");
}