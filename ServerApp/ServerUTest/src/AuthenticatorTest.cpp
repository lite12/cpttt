#include "stdafx.h"
#include <gtest\gtest.h>
#define private public
#include "include/Authenticator.h"
#undef public
#include <sstream>
#include <fstream>

using namespace ServerApp;

namespace ServerAppTest
{
    class UserStoreMock : IUserStore {
        std::unordered_map<std::string, std::shared_ptr<UserDefinition>> users;
    public:

        void addUser(std::string email, std::string key) {
            auto user = std::make_shared<UserDefinition>();
            user->key = key;
            user->email = email;
            users[key] = user;
        }
        virtual std::shared_ptr<UserDefinition> getUserViaKey(const std::string &key) const override {
            if (users.find(key) == users.end())
                return nullptr;
            return users.at(key);
        }
    };

    TEST(AuthenticatorTest, Auhtenticate) {
        std::string email = "test@test.com";
        std::string key = "123";
        auto store = new UserStoreMock();
        store->addUser(email, key);
        Authenticator auth((IUserStore*)store);
        EXPECT_TRUE(!auth.authenticate("", "").compare(""));
        EXPECT_TRUE(auth.authenticate(key, email).compare(""));
        EXPECT_TRUE(auth.authenticate(key, email).length() == Authenticator::k_tokenLength);
    }
    TEST(AuthenticatorTest, getUserViaToken) {
        std::string email = "test@test.com";
        std::string key = "123";
        auto store = new UserStoreMock();
        store->addUser(email, key);
        Authenticator auth((IUserStore*)store);
        auto token = auth.authenticate(key, email);
        auto user = auth.getUserBytoken(token);
        EXPECT_TRUE(user->key == key);
        EXPECT_TRUE(user->email == email);

    }
}  // namespace ServerAppTest
