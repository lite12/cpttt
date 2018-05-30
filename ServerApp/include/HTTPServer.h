/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_HTTPSERVER_H_
#define _SERVERAPP_HTTPSERVER_H_

#include "include/ServerResponse.h"
#include "shared/include/AppConfiguration.h"
#include <cpprest/http_listener.h>
#include <string>
#include <unordered_map>
#include <memory>

namespace ServerApp {
    using messageHandler = std::function<SERVER_REPONSE(const web::json::value& data)>;
    using http_listener_ = web::http::experimental::listener::http_listener;
    class HTTPServer
    {
        SharedLibs::configSection m_config;
        std::unordered_map<std::string, std::unique_ptr<http_listener_>> m_listeners;
        std::unordered_map<std::string, messageHandler> m_enpoints;

    public:
        bool start();
        bool stop();
        HTTPServer() {}
        HTTPServer(SharedLibs::configSection config) :m_config(config) {}
        ~HTTPServer();
        void registerEndPoint(const std::string& endpoint, messageHandler handler);
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_HTTPSERVER_H_

