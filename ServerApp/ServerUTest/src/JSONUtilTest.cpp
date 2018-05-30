#include "stdafx.h"
#include <gtest\gtest.h>
#include "shared/include/JSONUtil.h"
#include <sstream>
#include <fstream>

using namespace SharedLibs;

namespace ServerAppTest
{
    std::string email = "test@test.com";
    std::string key = "123";

    TEST(JSONUtilTest, ConvertToJSONString)
    {
        web::json::value val = JSONUtil::convertJsonString("test");
        EXPECT_TRUE(!val.as_string().compare(L"test"));
        web::json::value val2 = JSONUtil::convertJsonString("");
        EXPECT_TRUE(!val2.as_string().compare(L""));
    }

    TEST(JSONUtilTest, GetStringProperty)
    {
        web::json::value obj;
        obj[L"test"] = web::json::value::string(JSONUtil::wstr("test_value"));
        auto val = JSONUtil::getStringProperty(obj, "test");
        EXPECT_TRUE(!val.compare("test_value"));
    }
} // namespace ServerAppTest