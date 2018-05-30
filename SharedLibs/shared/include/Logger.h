#pragma once
#include <string>
#include <assert.h>
#include <fstream>
#include <memory>

namespace SharedLibs {
	class Logger
	{
		static constexpr char*  LOG_INFO = "INFO";
		static constexpr char*  LOG_ERROR = "ERROR";
		static Logger* s_instance;
		static  std::shared_ptr<std::ostream> s_file;
		Logger(const std::string &fileName);
		static void writelogMessage(const std::string& type, const std::string &message);
	public:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger rhs) = delete;
		
		static Logger* getInstance() {
			assert(s_instance);
			return s_instance;				
		}
		static void createInstance(const std::string &fileName);
		static void info(const std::string &message);
		static void error(const std::string &message);
		
	};
}
