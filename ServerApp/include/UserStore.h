/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_USERSTORE_H_
#define _SERVERAPP_USERSTORE_H_

#include "include/IUserStore.h"
#include "pugixml.hpp"
#include <string>
#include <memory>
#include <unordered_map>

namespace ServerApp {
    class UserStore : public IUserStore
    {
        std::unordered_map<std::string, std::shared_ptr<UserDefinition>> m_users;
        std::shared_ptr<UserDefinition>	createUserFromXml(const pugi::xml_node &node);
    public:
        std::shared_ptr<UserDefinition> getUserViaKey(const std::string& key) const override;
        UserStore(const std::string &userFile);
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_USERSTORE_H_
