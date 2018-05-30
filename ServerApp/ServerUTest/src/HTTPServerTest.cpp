#include "stdafx.h"
#include <gtest\gtest.h>
#include <gmock/gmock.h>
#include "include/HTTPServer.h"
#include "include/ServerResponse.h"
#include "shared/include/JSONUtil.h"
#include <cpprest/json.h>
#include <cpprest/http_client.h>

using ::testing::_;
using namespace web;                       
using namespace web::http;                 
using namespace web::http::client;
using namespace ServerApp;
using namespace SharedLibs;
namespace ServerAppTest
{
    class MessageHandler {
    public:
        SERVER_REPONSE handleEndPoint(const web::json::value & data) {
            return std::make_unique<web::json::value>();
        }
    };
    class HandlerMock :public MessageHandler {
    public:
        MOCK_METHOD1(handleEndPoint, SERVER_REPONSE(const web::json::value &));
    };

    TEST(HttpServer, RegisterEndPoint) {

        HTTPServer server;
        std::string endpoint = "http://localhost:8085/auth";
        HandlerMock mock;

        EXPECT_CALL(mock, handleEndPoint(_)).Times(1);
        server.registerEndPoint(endpoint, [&mock](const web::json::value &data)->ServerApp::SERVER_REPONSE {
            return mock.handleEndPoint(data);
        });
        server.start();
        std::wstring requestUrl(endpoint.begin(), endpoint.end());
        http_client client(requestUrl);
        web::json::value obj;
        obj[L"status"] = json::value::string(JSONUtil::wstr("str"));
        client.request(methods::POST).get();


    }
}  //namespace ServerAppTest