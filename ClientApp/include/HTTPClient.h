/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/

#ifndef _CLIENTAPP_HTTPCLIENT_H_
#define _CLIENTAPP_HTTPCLIENT_H_

#include "include/Response.h"
#include "shared/include/AppConfiguration.h"
#include "shared/include/JSONUtil.h"
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <memory>


namespace ClientApp {
    /**
    * \class HTTPClient
    * Used to communicate with server using JSON
    */

    class HTTPClient {
        web::http::client::http_client m_client;
        /// Client config comming from ini file
        SharedLibs::configSection m_config;

    public:
        HTTPClient() : m_client(U("http://localhost")) {}

        HTTPClient(SharedLibs::configSection config) :
            m_config(config),
            m_client(SharedLibs::JSONUtil::wstr(config["host"])) {}
        ~HTTPClient() {

        }
        virtual std::shared_ptr<Response> postRequest(const std::string& path, web::json::value& obj);
    };
}  // namespace ClientApp

#endif  // _CLIENTAPP_HTTPCLIENT_H_
