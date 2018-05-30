#include "stdafx.h"
#include "include/ServerResponse.h"
#include "shared/include/JSONUtil.h"

using namespace SharedLibs;

namespace ServerApp {
    SERVER_REPONSE ServerResponse::from(STATUS status, web::json::value response)
    {
        auto obj = std::make_shared<web::json::value>();;
        (*obj)[L"status"] = web::json::value(status);
        (*obj)[L"reponse"] = response;
        return obj;
    }

    SERVER_REPONSE ServerResponse::from(STATUS status, const std::string& response)
    {
        auto obj = std::make_shared<web::json::value>();;
        (*obj)[L"status"] = web::json::value(status);
        (*obj)[L"reponse"] = JSONUtil::convertJsonString(response);
        return obj;
    }

    SERVER_REPONSE ServerResponse::error(const std::string & errorMessage)
    {
        auto obj = std::make_shared<web::json::value>();;
        (*obj)[L"status"] = web::json::value(STATUS::ERROR);
        (*obj)[L"response"] = JSONUtil::convertJsonString(errorMessage);
        return obj;
    }

    SERVER_REPONSE ServerResponse::success(const std::string & message)
    {
        auto obj = std::make_shared<web::json::value>();;
        (*obj)[L"status"] = web::json::value(STATUS::OK);
        (*obj)[L"response"] = JSONUtil::convertJsonString(message);
        return obj;
    }

    ServerResponse::~ServerResponse()
    {
    }
}
