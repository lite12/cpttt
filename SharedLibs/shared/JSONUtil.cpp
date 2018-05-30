#include "stdafx.h"
#include <memory>
#include "include/JSONUtil.h"

namespace SharedLibs {
    std::string JSONUtil::getStringProperty(const web::json::value & val, const std::string& key)
    {
        try {
            auto keyVal = std::wstring(key.begin(), key.end());
            auto result = val.as_object().at(keyVal).as_string();
            return std::string(result.begin(), result.end());
        }
        catch (const std::exception &e) {
            return "";
        }
    }

    web::json::value JSONUtil::convertJsonString(const std::string & key)
    {
        return web::json::value::string(std::wstring(key.begin(), key.end()));
    }

    std::wstring JSONUtil::wstr(const std::string & str)
    {
        return std::wstring(str.begin(), str.end());
    }

    JSONUtil::JSONUtil()
    {
    }

    JSONUtil::~JSONUtil()
    {
    }
}  // namespace SharedLibs
