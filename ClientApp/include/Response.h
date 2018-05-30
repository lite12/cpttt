/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _CLIENTAPP_RESPONSE_H_
#define _CLIENTAPP_RESPONSE_H_

#include <cpprest/http_client.h>
#include <string>

namespace ClientApp {
    enum  STATUS { RES_OK = 1, RES_ERROR, AUTH_REQUIRED };
    class Response {
    public:
        // Server response status
        STATUS m_status;
        // Server response text
        std::string m_response;
        Response();
        Response(const Response& obj) {}
        Response(const web::http::http_response &response);
        Response(STATUS status, std::string& response) : m_status(status), m_response(response) {}
        ~Response();
    };
}  // namespace ClientApp

#endif  // _CLIENTAPP_RESPONSE_H_
