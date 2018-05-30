#include "stdafx.h"
#include "include/HTTPServer.h"
#include "shared/include/Logger.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace SharedLibs;

namespace ServerApp {
    bool HTTPServer::start()
    {
        Logger::info("Starting http server");

        for (auto &endpoint : m_enpoints) {
            std::unique_ptr<http_listener> newListener = std::make_unique<http_listener_>(std::wstring(endpoint.first.begin(), endpoint.first.end()));
            // Try to bind all end points and handlers
            newListener->support(methods::POST, [this, &endpoint](const http_request &request) {

                auto reqObj = request.extract_json().get();
                auto response = endpoint.second(reqObj);
                // Having nullptr means exception
                if (response == nullptr)
                    return request.reply(301);

                try {
                    return request.reply(web::http::status_codes::OK, *response);
                }
                catch (const std::exception& e) {
                    web::json::value obj;
                    obj[L"status"] = web::json::value::string(L"fail");
                    return request.reply(301, obj);
                }
            });
            try {
                newListener
                    ->open()
                    .wait();
                Logger::info("Listening on " + endpoint.first);
            }
            catch (exception const & e) {
                Logger::error("Unable to listen on " + endpoint.first);

                throw;
            }
        }
        return false;
    }

    bool HTTPServer::stop()
    {
        Logger::info("Stopping http server");
        for (const auto& listener : m_listeners) {
            listener.second->reset();
        }
        return false;
    }

    HTTPServer::~HTTPServer()
    {
        stop();
    }

    /// Register handler method for specific endpoint here
    void HTTPServer::registerEndPoint(const std::string & endpoint, messageHandler handler)
    {
        m_enpoints[endpoint] = handler;
    }
}  // namespace ServerApp
