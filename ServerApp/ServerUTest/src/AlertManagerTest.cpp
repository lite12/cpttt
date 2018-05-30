#include "stdafx.h"

#include "include/AlertManager.h"
#include "include/Application.h"
#include <gtest\gtest.h>
#include <gmock/gmock.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

using ::testing::_;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace ServerApp;
using namespace SharedLibs;

namespace ServerAppTest
{
    std::vector<std::string> getHighValues(int userVal, int dataVal) {
        auto user = std::make_shared<UserDefinition>();
        std::unordered_map<std::string, int> data;
        for (const auto &alert : Application::s_validAlerts) {
            user->alerts[alert] = userVal;
            data[alert] = dataVal;
        }
        AppConfiguration config;
        AlertManager alertManager(config);;
        return alertManager.getHighValues(*user, data);;
    }

    TEST(AlertManagerTest, getHighValues) {

        // All data values are high
        std::vector<std::string> highValues = getHighValues(0, 1);
        EXPECT_TRUE(highValues.size() == Application::s_validAlerts.size());

        // All data values are equal
        highValues = getHighValues(0, 0);
        EXPECT_TRUE(highValues.empty());

        // All data values are lower
        highValues = getHighValues(1, 0);
        EXPECT_TRUE(highValues.empty());
    }

}  //namespace ServerAppTest