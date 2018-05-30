#include "stdafx.h"

#include "include/HTTPClient.h"
#include "include/Response.h"
#include "shared/include/Logger.h"
#include <cpprest/json.h>
#include <cpprest/http_client.h>


using namespace web::http;
using namespace web::http::client;
using namespace SharedLibs;
namespace ClientApp {

    /** All http request will use this method.
      * It will send \b obj JSON object to specific \b path. Base url is defined
      * when object created.\n Having \b nullptr response means a network error
      */
    std::shared_ptr<Response> HTTPClient::postRequest(const  std::string& path, web::json::value& obj) {
        try {
            auto response = m_client.request(methods::POST, JSONUtil::wstr(path), obj).get();
            return std::make_shared<Response>(response);
        }
        catch (const web::http::http_exception &e) {
            std::error_code code = e.error_code();

            Logger::error("Network error while sending request:" + std::to_string(code.value()));
            return nullptr;
        }
        catch (const std::exception& e) {
            Logger::error("Error occured while sending request");
            return nullptr;
        }

    }
}  // namespace ClientApp
