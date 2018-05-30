#include "stdafx.h"
#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
namespace ServerApp {
	Logger * Logger::s_instance = nullptr;
	std::shared_ptr<std::ostream> Logger::s_file = nullptr;
	void Logger::createInstance(const std::string &fileName)
	{
		if (Logger::s_instance != nullptr)
			return;
		
		Logger::s_instance = new Logger(fileName);
	}
	void Logger::info(const std::string & message)
	{
		writelogMessage(LOG_INFO, message);
	}
	void Logger::error(const std::string & message)
	{
		writelogMessage(LOG_ERROR, message);
	}
	Logger::Logger(const std::string &fileName) {
		s_file = std::make_unique<std::ofstream>(fileName, std::ios_base::out | std::ios_base::app);
	}
	void Logger::writelogMessage(const std::string & type, const std::string & message)
	{
		std::time_t t = std::time(nullptr);
		auto timeExpr = std::put_time(std::localtime(&t), "[%c] ");
		try {
			if (s_file==nullptr || !s_file->good())
				return;
			std::cout << message<<std::endl;
			*s_file << timeExpr << type << ": " << message << std::endl;
			s_file->flush();

		}
		catch (const std::exception &e) {

		}
	}


	void info(const std::string &message)
	{
	}

}