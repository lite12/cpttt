/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_APPLICATION_H_
#define _SERVERAPP_APPLICATION_H_

#include "include/HTTPServer.h"
#include "include/IStorage.h"
#include "include/UserStore.h"
#include "include/AlertManager.h"
#include "include/Authenticator.h"
#include "include/ServerResponse.h"
#include "include/DbFactory.h"

#include "shared/include/AppConfiguration.h"
#include "shared/include/Logger.h"
#include <cpprest/json.h>
#include <string>
#include <memory>

namespace ServerApp {

    class Application
    {
        
        const char* m_configFileName;
        const std::string m_userFile{ "server_config.xml" };
        SharedLibs::AppConfiguration m_appConfig;
        HTTPServer m_server;
        UserStore m_userStore;
        AlertManager m_alertManager;
        std::shared_ptr<IStorage> m_storage;
        Authenticator m_authenticator;

    public:
        static  std::vector<std::string> s_validAlerts;
        Application() = delete;
        explicit Application(const char* config) : m_configFileName(config),
            m_appConfig(config),
            m_userStore(m_userFile),
            m_authenticator(&m_userStore),
            m_alertManager(m_appConfig),
            m_storage(DBFactory::getStorageImpl(DBType::MySql,m_appConfig.get("database"))),
            m_server(m_appConfig.get("server")) {
            SharedLibs::Logger::createInstance("server_log.txt");
            m_server.registerEndPoint(m_appConfig.get("server")["auth"], [this](const web::json::value &data)->ServerApp::SERVER_REPONSE {
                return this->handleAuthentication(data);
            });
            m_server.registerEndPoint(m_appConfig.get("server")["record"], [this](const web::json::value &data)->ServerApp::SERVER_REPONSE { return this->handleRecord(data); });
        }

        std::unordered_map<std::string, int> getValidData(const web::json::value & data);
        ServerApp::SERVER_REPONSE handleAuthentication(const web::json::value &data);
        ServerApp::SERVER_REPONSE handleRecord(const web::json::value &data);
        void start();

        ~Application();
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_APPLICATION_H_
