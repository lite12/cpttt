/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_MYSQLSTORAGE_H
#define _SERVERAPP_MYSQLSTORAGE_H

#include "include/IStorage.h"
#include "shared/include/AppConfiguration.h"
#include "soci.h"
#include "soci-odbc.h"
#include <string>
#include <unordered_map>
#include <memory>
namespace ServerApp {
	class MySQLStorage : public IStorage
	{
        std::shared_ptr< soci::session> sql;
        SharedLibs::configSection m_config;
	public:
		bool addRecord(const std::string&key,std::unordered_map<std::string,int> data) override;
		bool connect();

        MySQLStorage(SharedLibs::configSection config) :m_config(config) {}
		~MySQLStorage();
	};
}  // namespace ServerApp

#endif // _SERVERAPP_MYSQLSTORAGE_H