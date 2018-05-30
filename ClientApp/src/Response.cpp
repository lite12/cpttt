#include "stdafx.h"

#include "include/Response.h"
#include "shared/include/JSONUtil.h"
namespace ClientApp {

    Response::Response() {
    }

    Response::Response(const web::http::http_response &response) {
        auto jsonValue = response.extract_json().get();
        m_status = (STATUS)jsonValue.at(L"status").as_integer();
        m_response = SharedLibs::JSONUtil::getStringProperty(jsonValue, "response");
    }

    Response::~Response() {
    }
}  //namespace ClientApp
