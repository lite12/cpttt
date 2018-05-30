#include "stdafx.h"
#include <gtest\gtest.h>
#include "include/UserStore.h"
#include <sstream>
#include <fstream>

using namespace ServerApp;

namespace ServerAppTest
{
    std::string defaultKey = "123";
    std::string defaultEmail = "user1@test.com";
    int alertMemory = 50;
    int alertCpu = 20;
    int processes = 30;

    std::unique_ptr<UserStore> defaultUserStore() {
        std::ofstream defaultFile("default.xml");
        defaultFile << "<client key = \"" << defaultKey << "\" mail = \"" << defaultEmail << "\">";
        defaultFile << "<alert type = \"memory\" limit = \"" << alertMemory << "%\" />";
        defaultFile << "<alert type = \"cpu\" limit = \"" << alertCpu << "%\" />";
        defaultFile << "<alert type = \"processes\" limit = \"" << processes << "\" />";
        defaultFile << "</client>";

        defaultFile.flush();
        return std::make_unique<UserStore>("default.xml");
    }

    TEST(UserStore, FileNotExists) {
        ASSERT_THROW(ServerApp::UserStore newStore("invalid_xml.xml"), std::exception);
    }

    TEST(UserStore, InvalidXml) {
        std::ofstream empty_file("empty_xml.xml");
        empty_file.flush();
        ASSERT_THROW(ServerApp::UserStore newStore("empty_xml.xml"), std::exception);
    }

    TEST(UserStore, MultipleSameKey)
    {
        std::ofstream multipKeyFile("multiple_.xml");
        multipKeyFile << "<client key = \"123\" mail = \"user1@ahmet.com\">";
        multipKeyFile << "</client>";
        multipKeyFile << "<client key = \"123\" mail = \"user2@ahmet.com\">";
        multipKeyFile << "</client>";
        multipKeyFile.flush();

        ASSERT_THROW(ServerApp::UserStore newStore("multiple_.xml"), std::exception);
    }

    TEST(UserStore, GetUserViaKey)
    {
        auto store = defaultUserStore();
        auto user = store->getUserViaKey("1");
        EXPECT_TRUE(user == nullptr);
        auto user2 = store->getUserViaKey(defaultKey);
        ASSERT_TRUE(user2 != nullptr);
        EXPECT_TRUE(!user2->key.compare(defaultKey));
        EXPECT_TRUE(!user2->email.compare(defaultEmail));
    }

    TEST(UserStore, GetUserViaAlerts)
    {
        auto store = defaultUserStore();
        auto user2 = store->getUserViaKey(defaultKey);

        ASSERT_TRUE(user2 != nullptr);
        EXPECT_TRUE(user2->alerts["cpu"] == alertCpu);
        EXPECT_TRUE(user2->alerts["memory"] == alertMemory);
        EXPECT_TRUE(user2->alerts["processes"] == processes);
    }
}  // namespace ServerAppTest