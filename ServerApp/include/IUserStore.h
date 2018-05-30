/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_IUSERSTORE_H_
#define _SERVERAPP_IUSERSTORE_H_

#include <string>
#include <unordered_map>
#include <memory>

namespace ServerApp {
    struct UserDefinition {
        std::string email;
        std::string key;
        std::unordered_map<std::string, int> alerts;
    };
    class IUserStore
    {
    public:
        virtual std::shared_ptr<UserDefinition> getUserViaKey(const std::string &key) const = 0;
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_IUSERSTORE_H_
