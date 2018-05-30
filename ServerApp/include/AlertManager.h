/**
 * @author Ahmet Emir Ercin
 * @date  26 Sep 2017
 */
#ifndef _SERVERAPP_ALERTMANAGER_H_
#define _SERVERAPP_ALERTMANAGER_H_

#include "include/SMTPClient.h"
#include "include/UserStore.h"

#include "shared/include/AppConfiguration.h"
namespace ServerApp {
    class AlertManager
    {
        SMTPClient m_mailClient;
    public:
        void newDataArrived(const UserDefinition& user,  std::unordered_map<std::string, int> data);
        std::vector<std::string> getHighValues(const UserDefinition & user, std::unordered_map<std::string, int> data);
        std::string generateAlertMessage(std::vector<std::string> highAlerts, std::unordered_map<std::string, int> data);
        
        AlertManager(SharedLibs::AppConfiguration config) :m_mailClient(config.get("mail"))
        {
        };
        ~AlertManager();
    };
}  // namespace ServerApp

#endif  // _SERVERAPP_ALERTMANAGER_H_
