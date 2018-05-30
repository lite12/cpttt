#include "stdafx.h"
#include <gtest\gtest.h>
#include "include/SystemInfoCollector.h"
#include <sstream>
#include <fstream>

using namespace ClientApp;

namespace ServerAppTest
{
	TEST(SystemInfoCollectorTest, getMemory)
	{
		SystemInfoCollector collector;
		collector.init();
		auto systemInfo=collector.getSystemInfo();
		EXPECT_TRUE(systemInfo->cpuUsage >= 0);
		EXPECT_TRUE(systemInfo->memUsage > 0);
		EXPECT_TRUE(systemInfo->processCount > 0);

	}
}  // namespace ServerAppTest