/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_ISTORAGE_H_
#define _SERVERAPP_ISTORAGE_H_

#include <string>
#include <unordered_map>
namespace ServerApp {
	class IStorageConfig {
		std::string host;
		std::string username;
		std::string password;
		std::string database;
		std::string table;
	};
	class IStorage {

    public:
		virtual bool addRecord(const std::string&key, std::unordered_map<std::string, int> data) = 0;
		virtual bool connect() = 0;
	};
}  // namespace ServerApp

#endif  //_SERVERAPP_ISTORAGE_H_ 