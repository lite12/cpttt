#include "stdafx.h"

#include "include/MySQLStorage.h"


using namespace soci;
using namespace std;

namespace ServerApp {

    bool MySQLStorage::addRecord(const std::string&key, std::unordered_map<std::string, int> data)
    {
        try {
            for (const auto& val : data)
                *sql << "insert into user_records value(NULL,'" << key << "','" << val.first << "','" << val.second << "')";

            return true;
        }
        catch (const std::exception &e) {
            return false;
        }
    }

    bool MySQLStorage::connect()
    {
        sql = std::make_shared< soci::session>(odbc, "DSN=" + m_config.at("dsn"));
        return true;
    }

    MySQLStorage::~MySQLStorage()
    {
    }
} // namespace ServerApp
