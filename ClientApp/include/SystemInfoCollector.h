/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#ifndef _CLIENTAPP_SYSTEMINFO_H_
#define _CLIENTAPP_SYSTEMINFO_H_

#include <pdh.h>
#include <memory>

namespace ClientApp {
    struct SystemInfoObject {
        int cpuUsage;
        int memUsage;
        int processCount;
        time_t time;
        bool inQueue;
    };

    class SystemInfoCollector {
        static  bool s_cpuQueryInited;;
        int getMemoryUsage() const;
        int getCpuUsage() const;
        int getProcessCount() const;
        static PDH_HQUERY s_cpuQuery;
        static PDH_HCOUNTER s_cpuTotal;

    public:
        std::shared_ptr<SystemInfoObject> getSystemInfo();
        static void init();
        SystemInfoCollector();
        ~SystemInfoCollector();
    };
}  // namespace ClientApp

#endif  // _CLIENTAPP_SYSTEMINFO_H_
