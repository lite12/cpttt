#include "stdafx.h"
#include "include/AppConfiguration.h"

namespace SharedLibs {

    /// Convert ini sections to map<string,string>
    SharedLibs::configSection AppConfiguration::readConfigSection(boost::property_tree::basic_ptree<std::string, std::string> section)
    {
        configSection newSection;
        for (const auto& it : section) {
            newSection[it.first] = it.second.get_value("");
        }
        return newSection;
    }

    /// Read app configuration from ini file
    AppConfiguration::AppConfiguration(const char* fileName)
    {
        boost::property_tree::ptree pt;
        try {
            boost::property_tree::ini_parser::read_ini(fileName, pt);
            for (const auto& it : pt) {
                m_sections[it.first] = readConfigSection(it.second);
            }
        }
        catch (const boost::property_tree::ini_parser_error &e) {
            throw std::exception("Unable to load config file");
        }
        catch (...) {
            throw;
        }
    }

    AppConfiguration::~AppConfiguration()
    {
    }
}  // namespace SharedLibs