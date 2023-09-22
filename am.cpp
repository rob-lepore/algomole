#include "am.h"

#include "exceptions/missingoptionexception.h"
#include "exceptions/invalidoptionexception.h"
#include <iostream>




float am::pipeline::options::getOption(std::unordered_map<std::string, float>& options, std::string key, float defaultValue) {
	if (options.find(key) != options.end()) {
		return options[key];
	}
	else {
		std::cout << "Using " + key + " = " + std::to_string(defaultValue) + "\n";
		options[key] = defaultValue;
		return defaultValue;
	}
}


float am::pipeline::options::getOptionWithError(std::unordered_map<std::string, float>& options, std::string key) {
	if (options.find(key) != options.end()) {
		return options[key];
	}
	else {
		throw MissingOptionException(key);
		return 0;
	}
}

void am::pipeline::options::assertOptionValue(std::unordered_map<std::string, float>& options, std::string key, float value){
	if (options.find(key) == options.end()) {
		throw MissingOptionException(key);
	}
	if (options[key] != value) {
		throw InvalidOptionException(key, value);
	}
}



