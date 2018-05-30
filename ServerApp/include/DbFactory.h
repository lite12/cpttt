/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/

#ifndef _SERVERAPP_DBFACTORY_H_
#define _SERVERAPP_DBFACTORY_H_

#include "include/IStorage.h"
#include "shared/include/AppConfiguration.h"
#include <memory>

namespace ServerApp {
    enum class DBType {
        MySql,
        MongoDB
    };
    class DBFactory
    {
    public:
        DBFactory();
        ~DBFactory();
        static std::shared_ptr<IStorage> getStorageImpl(DBType dbType,const SharedLibs::configSection& config);
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_DBFACTORY_H_
