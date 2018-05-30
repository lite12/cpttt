#include "stdafx.h"
#include "include/AlertManager.h"
#include "shared/include/Logger.h"

using namespace SharedLibs;

namespace ServerApp {

    /// Compares users alert definition with incoming data and send alert e-mail if any of them is high
	void AlertManager::newDataArrived(const UserDefinition & user, std::unordered_map<std::string,int> data )
	{
        std::vector<std::string> highValueDefs = getHighValues(user, data);
        if (!highValueDefs.empty()) {
            try {
                std::string alertMessage = generateAlertMessage(highValueDefs, data);
                m_mailClient.send("Alert Notification", alertMessage);
            }
            catch (const std::exception& error) {
                Logger::error("Error while sending alert e-mail!");
            }
        }		
	}

    std::vector<std::string> AlertManager::getHighValues(const UserDefinition & user, std::unordered_map<std::string, int> data)
    {
        std::vector<std::string> highValueAlertDef;
        for (auto& alertDef : data) {
            if (user.alerts.find(alertDef.first) != user.alerts.end()) {
                if (data[alertDef.first] > user.alerts.at(alertDef.first)) {
                    /// Incoming data> User Alert Definition
                    highValueAlertDef.push_back(alertDef.first);
                }
            }
        }
        return highValueAlertDef;
    }

    std::string AlertManager::generateAlertMessage(std::vector<std::string> highAlerts, std::unordered_map<std::string, int> data)
    {
        std::stringstream ss;
        for (const auto& alertDef : highAlerts) {
            ss << alertDef<<":"<<data[alertDef];
        }
        return ss.str();
    }

	AlertManager::~AlertManager()
	{
	}
} // namespace ServerApp
