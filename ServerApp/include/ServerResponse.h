/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _SERVERAPP_SERVERRESPONSE_H_
#define _SERVERAPP_SERVERRESPONSE_H_

#include <cpprest/json.h>
#include <string>
#include <memory>

namespace ServerApp {
    using SERVER_REPONSE = std::shared_ptr<web::json::value>;
    class ServerResponse
    {

    public:
        enum  STATUS { OK = 1, ERROR, AUTH_REQUIRED };
        static SERVER_REPONSE from(STATUS status, web::json::value response);
        static SERVER_REPONSE from(STATUS status, const std::string& response);
        static SERVER_REPONSE error(const std::string &errorMessage);
        static SERVER_REPONSE success(const std::string & message);
        ~ServerResponse();
    };

}  // namespace ServerApp

#endif // namespace _SERVERAPP_SERVERRESPONSE_H_
