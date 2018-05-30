/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/

#ifndef _CLIENTAPP_APPLICATION_H_
#define _CLIENTAPP_APPLICATION_H_

#include <string>
#include <iostream>
#include <memory>
#include <queue>
#include "include/SystemInfoCollector.h"
#include "shared/include/AppConfiguration.h"
#include "include/HTTPClient.h"
#include "shared/include/Logger.h"
namespace ClientApp {
    /**
    * \class Application
    * All application related logic defined here
    */
    class Application {
    private:
        /// Retry count after getting network error for auth request
        int m_authRetry = 10;

        /// Delay to wait between auth request
        static constexpr int k_authRetryDelay = 10 * 100;
        /// Max queue size to store sysInfo objects
        static constexpr int k_maxQueueItem = 3;
        /// Authenticateion token
        std::string m_token;

        SharedLibs::AppConfiguration m_appConfig;
        /// User config (email,key) from ini file
        SharedLibs::configSection m_userConfig;
        /// Client config from ini file
        SharedLibs::configSection m_clientConfig;
        SystemInfoCollector m_dataCollector;
        std::shared_ptr<HTTPClient> m_client;
        /// Object to collect system information
        std::queue<std::shared_ptr<SystemInfoObject>> m_sysInfoQueue;

        void authenticate(const std::string& key, const std::string& email);

    public:
        Application(const char* config, std::shared_ptr<HTTPClient> httpClient = nullptr) :
            m_appConfig(config),
            m_userConfig(m_appConfig.get("user")),
            m_clientConfig(m_appConfig.get("client")),
            m_client(httpClient != nullptr ? httpClient : std::make_shared<HTTPClient>(m_clientConfig)) {
            SharedLibs::Logger::createInstance("client_log.txt");
            SystemInfoCollector::init();
        }

        void waitSendingInformation();
        void queueInfoObject(std::shared_ptr<SystemInfoObject> sysInfo);
        std::shared_ptr<SystemInfoObject> getSystemInfoObject();
        void tryAuthentication();

        void start();
        bool sendData(std::shared_ptr<SystemInfoObject> sysInfo);

    };
}  // namespace ClientApp

#endif  // _CLIENTAPP_APPLICATION_H_
