#include "Logger.h"
#include "glm/gtx/string_cast.hpp"
using namespace am::utils;

Logger::Logger(std::string activity, std::ostream& outputStream) : m_activity(activity), m_out(outputStream) {
	
}

void Logger::log(std::string msg, std::string end) {
	m_out << "[" << m_activity << "]  " << msg << end;
}


void Logger::startTimer() {
	m_start = std::chrono::high_resolution_clock::now();
}

void Logger::logElapsedTime(std::string message) {
	m_stop = std::chrono::high_resolution_clock::now();
	log(message + " -> [ " + std::to_string((m_stop - m_start).count() / 1000000) + " ms ]");
}