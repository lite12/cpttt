#include "stdafx.h"
#include "include/Authenticator.h"
#include "include/UserStore.h"
#include "shared/include/Logger.h"
#include <random>
#include <sstream>

using namespace SharedLibs;

namespace ServerApp {

    /// Generate random string to be used as user auth token
    std::string Authenticator::generateToken()
    {
        std::string chars(
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890");
        std::stringstream ss;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(1.0, chars.length());
        for (int i = 0; i < k_tokenLength; ++i) {
            ss << chars[dist(mt)];
        }
        return ss.str();
    }

    Authenticator::~Authenticator()
    {
    }

    /// Check if token associated with any user
    bool Authenticator::verifyToken(const std::string & token)
    {
        return m_tokens.find(token) != m_tokens.end();
        return false;
    }

    /// Authenticate user accroding to key
    std::string Authenticator::authenticate(const std::string& key, const std::string& email)
    {
        auto user = m_userStore->getUserViaKey(key);
        if (user == nullptr || email.compare(user->email)) {
            Logger::error("Invalid authentication attempt for user " + email);
            return std::string();
        }
        auto token = generateToken();
        m_tokens[token] = key;
        return token;
    }
    /// Find user with provided auth token
    std::shared_ptr<UserDefinition> Authenticator::getUserBytoken(const std::string & token)
    {
        if (m_tokens.find(token) == m_tokens.end())
            return nullptr;
        std::string key = m_tokens.at(token);
        return m_userStore->getUserViaKey(key);
    }
} // namespace ServerApp