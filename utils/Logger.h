#pragma once
#include "../am.h"
#include <iostream>
#include <chrono>
/**
 * @brief The Logger class provides functionality for logging activities and measuring time.
 */
class am::utils::Logger
{
public:
	/**
	 * @brief Constructor for the Logger class.
	 *
	 * @param activity The name of the activity that will be shown in every message.
	 * @param outputStream The output stream to write log messages to (default is std::cout).
	 */
	Logger(std::string activity, std::ostream& outputStream = std::cout);
	
	/**
	 * @brief Logs a message with an optional end character (default is newline).
	 *
	 * @param msg The message to be logged.
	 * @param end The character to append at the end of the log message (default is newline).
	 */
	void log(std::string msg, std::string end = "\n");

	/**
	* @brief Starts a timer to measure elapsed time.
	*/
	void startTimer();

	/**
	 * @brief Logs the elapsed time since the timer was started with an optional message.
	 *
	 * @param message The optional message to log along with the elapsed time.
	 */
	void logElapsedTime(std::string message = "");

private:
	std::ostream& m_out;
	std::string m_activity;
	std::chrono::steady_clock::time_point m_start, m_stop;

};

