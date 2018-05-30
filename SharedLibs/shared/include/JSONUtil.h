#pragma once
#include <string>
#include <cpprest/json.h>
namespace SharedLibs {
	class JSONUtil
	{
	public:
		static std::string getStringProperty(const web::json::value& val, const std::string& key);
		static web::json::value convertJsonString(const std::string& key);
		static std::wstring wstr(const std::string& str);
		JSONUtil();
		~JSONUtil();

	};
}

