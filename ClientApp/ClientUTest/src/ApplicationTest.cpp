#include "stdafx.h"
#include <gtest\gtest.h>
#include <gmock\gmock.h>
#define private public
#include "include/Application.h"
#undef private
#include "include/HTTPClient.h"
#include "include/Response.h"
#include <sstream>
#include <fstream>
#include <memory>

using namespace ClientApp;
using ::testing::_;
using ::testing::DefaultValue;
using ClientResponse = std::shared_ptr<Response>;

namespace ClientAppTest
{
    void createDefaultConfig() {
        std::ofstream file("client_config_test.ini");
        file << "[client]" << std::endl;
        file << "host = http://localhost:8085" << std::endl;
        file << "auth = / auth" << std::endl;
        file << "delay = 2" << std::endl;
        file << "[user]" << std::endl;
        file << "email = user1@user.com" << std::endl;
        file << "key = 123" << std::endl;
        file.flush();
        file.close();
    }

    class HTTPClientImpl :public HTTPClient {
    public:
        int m_callCount;
        bool m_netWorkError;
        STATUS m_returnType;
        std::string m_responseStr;

        void setReturnValue(STATUS returnType, std::string& responseStr) {
            m_returnType = returnType;
            m_responseStr = responseStr;
        }
        std::shared_ptr<Response> postRequest(const std::string& path, web::json::value& obj) override {
            m_callCount++;
            if (m_netWorkError)
                return nullptr;
            return std::make_shared<Response>(m_returnType, m_responseStr);
        }
    };

    TEST(ApplicationTest, InvalidCredentials)
    {
        createDefaultConfig();
        auto httpClient = std::make_shared<HTTPClientImpl>();
        std::shared_ptr<HTTPClient> httpClientMock = std::static_pointer_cast<HTTPClient>(httpClient);
        Application app("client_config_test.ini", httpClientMock);

        EXPECT_THROW(app.tryAuthentication();, std::exception);
    }

    TEST(ApplicationTest, ValidToken)
    {
        createDefaultConfig();
        auto httpClient = std::make_shared<HTTPClientImpl>();
        std::string token = "token_str";
        httpClient->setReturnValue(STATUS::RES_OK, token);
        std::shared_ptr<HTTPClient> httpClientMock = std::static_pointer_cast<HTTPClient>(httpClient);
        Application app("client_config_test.ini", httpClientMock);
        app.tryAuthentication();
        EXPECT_TRUE(!app.m_token.compare(token));
    }

    TEST(ApplicationTest, TokenNetworkError)
    {
        createDefaultConfig();
        auto httpClient = std::make_shared<HTTPClientImpl>();
        httpClient->m_callCount = 0;
        httpClient->m_netWorkError = true;

        std::shared_ptr<HTTPClient> httpClientMock = std::static_pointer_cast<HTTPClient>(httpClient);
        Application app("client_config_test.ini", httpClientMock);

        try {
            app.tryAuthentication();
        }
        catch (const std::exception&) {

        }
        EXPECT_TRUE(httpClient->m_callCount == 3);
    }

    TEST(ApplicationTest, CollectSystemInformation)
    {
        createDefaultConfig();
        auto httpClient = std::make_shared<HTTPClientImpl>();
        httpClient->m_callCount = 0;
        httpClient->m_netWorkError = true;

        
        Application app("client_config_test.ini");
        std::shared_ptr<SystemInfoObject> sysInfo= app.getSystemInfoObject();
        ASSERT_TRUE(sysInfo != nullptr);
        EXPECT_TRUE(sysInfo->cpuUsage >= 0);
        EXPECT_TRUE(sysInfo->memUsage >= 0);
        EXPECT_TRUE(sysInfo->processCount > 0);
        
    }
}  // namespace ClientAppTest