#include "stdafx.h"

#include "include/SystemInfoCollector.h"
#include <windows.h>
#include <psapi.h>
#include <ctime>
#include <cassert>
#pragma comment(lib, "pdh.lib")

namespace ClientApp {
    bool SystemInfoCollector::s_cpuQueryInited = false;

    PDH_HQUERY SystemInfoCollector::s_cpuQuery = nullptr;
    PDH_HCOUNTER SystemInfoCollector::s_cpuTotal = nullptr;

    int SystemInfoCollector::getMemoryUsage() const {
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        return statex.dwMemoryLoad;
    }

    int SystemInfoCollector::getCpuUsage() const {
        assert(s_cpuQueryInited);
        PDH_FMT_COUNTERVALUE counterVal;
        try {
            PdhCollectQueryData(SystemInfoCollector::s_cpuQuery);
            PdhGetFormattedCounterValue(SystemInfoCollector::s_cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
            return static_cast<int>(counterVal.doubleValue);
        }
        catch (...) {
            return 0;
        }
    }

    /// This is needed to register cpu query
    void SystemInfoCollector::init() {
        PdhOpenQuery(NULL, NULL, &s_cpuQuery);
        PdhAddEnglishCounter(s_cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &s_cpuTotal);
        PdhCollectQueryData(s_cpuQuery);
        s_cpuQueryInited = true;
    }

    int SystemInfoCollector::getProcessCount() const {
        DWORD aProcesses[1024], cbNeeded;
        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            return 0;
        }

        return cbNeeded / sizeof(DWORD);
    }

    std::shared_ptr<SystemInfoObject> SystemInfoCollector::getSystemInfo() {
        auto sysInfo = std::make_shared<SystemInfoObject>();
        sysInfo->memUsage = getMemoryUsage();
        sysInfo->processCount = getProcessCount();
        sysInfo->cpuUsage = getCpuUsage();
        sysInfo->time = std::time(new time_t());
        sysInfo->inQueue = false;
        return sysInfo;
    }

    SystemInfoCollector::SystemInfoCollector() {
    }

    SystemInfoCollector::~SystemInfoCollector() {
    }
}  // namespace ClientApp
