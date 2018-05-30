#include "stdafx.h"

#include "include/Application.h"
#include "shared/include/Logger.h"
#include <thread>

using namespace SharedLibs;
namespace ClientApp {
    void Application::start() {
        bool _execute = true;
        // Required for CPU usage query initialization
        SystemInfoCollector::init();
        tryAuthentication();

        int delay = std::stoi(m_clientConfig["delay"]);
        std::thread([=]() {
            while (_execute) {
                auto sysInfo = getSystemInfoObject();
                waitSendingInformation();
                sendData(sysInfo);

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(delay * 1000));
            }
        }).detach();
    }

    void Application::tryAuthentication() {
        authenticate(m_userConfig["email"], m_userConfig["key"]);
    }

    /** If there is a network error or auth problem, statistics will be queued.\n
      * If queue size becomes largen then \b k_maxQueueItem app will fail
      *
      */
    void Application::waitSendingInformation() {
        size_t itemPassed = m_sysInfoQueue.size();
        while (!m_sysInfoQueue.empty() && --itemPassed) {
            auto sysInfo = m_sysInfoQueue.front();
            if (sendData(sysInfo)) {
                m_sysInfoQueue.pop();
            }
        }
    }

    // Add sysInfo object to queue if queue size is smaller than \b m_sysInfoQueue
    void Application::queueInfoObject(std::shared_ptr<SystemInfoObject> sysInfo) {
        if (sysInfo == nullptr || sysInfo->inQueue == true)
            return;
        Logger::info("SysInfo queue size:" + std::to_string(m_sysInfoQueue.size()));

        //Since we are retrying to send each item and these consume extra time,
        //total time to send queue should be less than data collection interval
        if (m_sysInfoQueue.size() == k_maxQueueItem) {
            Logger::error("Unable to add more sysInfo to queue!");
            return;
        }
        m_sysInfoQueue.push(sysInfo);
        sysInfo->inQueue = true;
    }

    // Collects system information like cpu,mem and process count
    std::shared_ptr<SystemInfoObject> Application::getSystemInfoObject() {
        try {
            auto sysInfo = m_dataCollector.getSystemInfo();
            return sysInfo;
        }
        catch (const std::exception& e) {
            Logger::error("Unable to collect system information");
            return nullptr;
        }
    }

    /** Will try to get an authentication token.In case of network error
     * we wil try \b m_authRetry times. App will fail after getting "invalid credentials" since
     * no way to recover
     */
    void Application::authenticate(const std::string & key, const std::string & email) {
        web::json::value obj;
        obj[L"key"] = SharedLibs::JSONUtil::convertJsonString(key);
        obj[L"email"] = SharedLibs::JSONUtil::convertJsonString(email);
        auto response = m_client->postRequest("/auth", obj);
        if (response == nullptr) {
            //Network error,need to retry again
            if (m_authRetry <= 1)
                throw std::exception("Unable to authenticate");
            m_authRetry--;

            //Wait |k_authRetryDelay| and retry |m_authRetry| times
            //Fail if all attemps fails
            Logger::info("Will try to authenticate again...");
            std::this_thread::sleep_for(
                std::chrono::milliseconds(Application::k_authRetryDelay));
            tryAuthentication();
            return;
        }

        if (response->m_status == STATUS::RES_OK) {
            m_token = response->m_response;
            Logger::info("Sucessfully authenticated.");
        }
        else {
            //Authentication error, no need to retry possibly wrong crendetials
            throw std::exception(response->m_response.c_str());
        }
    }

    /** Try to send collected system information.\n In case of network error data will be queed.
     * \n Will try to re authenticate after getting authentication error.This is only posssible if server
     * goes down after we authenticated
     */
    bool Application::sendData(std::shared_ptr<SystemInfoObject> sysInfo) {
        assert(!m_token.empty());
        web::json::value obj;
        obj[L"cpu"] = web::json::value(sysInfo->cpuUsage);
        obj[L"mem"] = web::json::value(sysInfo->memUsage);
        obj[L"process"] = web::json::value(sysInfo->processCount);
        obj[L"token"] = m_token;
        std::stringstream ss;
        Logger::info("System Information");
        ss << "CPU:" << sysInfo->cpuUsage << " Memory:" << sysInfo->memUsage << " Processes:" << sysInfo->processCount;
        Logger::info(ss.str());

        auto response = m_client->postRequest("/new-record", obj);
        if (response == nullptr) {
            queueInfoObject(sysInfo);
            Logger::error("Unable to send system information!");
            return false;
        }
        else if (response->m_status == STATUS::AUTH_REQUIRED) {
            Logger::error("Authentication required!");
            queueInfoObject(sysInfo);
            tryAuthentication();
            return false;
        }
        else {
            return true;
        }
    }
}  // namespace ClientApp
