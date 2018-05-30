/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_AUTHENTICATOR_H_
#define _SERVERAPP_AUTHENTICATOR_H_

#include "include/IUserStore.h"
#include <string>
#include <unordered_map>
#include <memory>

namespace ServerApp {
    class Authenticator
    {
    private:
        /// Auth token length
        static constexpr int k_tokenLength = 32;
        /// Map for <auth token,user unique key>
        std::unordered_map<std::string, std::string> m_tokens;
        std::string generateToken();
        /// Used to retrive user information via keys
        IUserStore* m_userStore;
    public:
        Authenticator(IUserStore* userStore) :m_userStore(userStore) {}
        ~Authenticator();
        bool verifyToken(const std::string& token);
        std::string authenticate(const std::string& key, const std::string& email);
        std::shared_ptr<UserDefinition> getUserBytoken(const std::string& token);
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_AUTHENTICATOR_H_