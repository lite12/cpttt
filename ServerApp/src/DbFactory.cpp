#include "stdafx.h"
#include "include/DbFactory.h"
#include "include/MySQLStorage.h"
#include "shared/include/AppConfiguration.h"
using namespace std;
using namespace SharedLibs;
namespace ServerApp {
	DBFactory::DBFactory()
	{
	}

	DBFactory::~DBFactory()
	{
	}

	std::shared_ptr<IStorage> DBFactory::getStorageImpl(DBType dbType, const configSection& config)
	{
		switch (dbType)
		{
		case DBType::MySql:
			return std::make_shared<MySQLStorage>(config);
		default:
			throw("Unknow database type");
		}
		return nullptr;

	}

}