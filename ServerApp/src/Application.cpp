/**
 * @author Ahmet Emir Ercin
 * @date  26 Sep 2017
 */

#include "stdafx.h"
#include "include/Application.h"
#include "include/UserStore.h"

#include "shared/include/Logger.h"
#include "shared/include/JSONUtil.h"

using namespace std;
using namespace web;
using namespace SharedLibs;
namespace ServerApp {
   std::vector<std::string> Application::s_validAlerts= { "cpu", "mem", "process" };
    std::unordered_map<std::string, int> Application::getValidData(const web::json::value & data)
    {
        std::unordered_map<std::string, int> validData;
        for (const auto& validAlert : s_validAlerts) {
            if (data.has_field(JSONUtil::wstr(validAlert))) {
                validData[validAlert] = data.at(JSONUtil::wstr(validAlert)).as_integer();
            }
        }
        return validData;
    }
    /** Handle authentication request. Expects to get unique user key and email to check
      * to check with server_config.xml
      */
    ServerApp::SERVER_REPONSE Application::handleAuthentication(const web::json::value & data)
    {
        auto key = JSONUtil::getStringProperty(data, "key");
        auto email = JSONUtil::getStringProperty(data, "email");
        if (key.empty() || email.empty())
        {
            return ServerResponse::error("Missing parameters for authentication!");
        }
        Logger::info("Authentication request for " + email);
        auto token = m_authenticator.authenticate(key, email);
        if (token.empty())
            return ServerResponse::error("Invalid credentials!");
        return ServerResponse::success(token);
    }

    /// Handle statistics record request
    ServerApp::SERVER_REPONSE Application::handleRecord(const web::json::value & data)
    {
        auto token = JSONUtil::getStringProperty(data, "token");
        if (!m_authenticator.verifyToken(token))
            return ServerResponse::from(ServerResponse::STATUS::AUTH_REQUIRED, "Authentication required");
        std::shared_ptr<UserDefinition> user = m_authenticator.getUserBytoken(token);

        /// Filter incoming data to give alerts
        std::unordered_map<std::string, int> validData = getValidData(data);
        m_alertManager.newDataArrived(*user, validData);

        if(m_storage->addRecord(user->key,validData))
            return ServerResponse::success("Saved");
        else
            return ServerResponse::error("Unable to save your data");
    }

    void Application::start()
    {
        m_storage->connect();
        m_server.start();
    }

    Application::~Application()
    {
    }
}  // namespace ServerApp
