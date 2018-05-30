// ServerApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "include/Application.h"
#include <string>
#include <memory>

using namespace ServerApp;
int main()
{
    std::unique_ptr<Application> app;
    try {
        app = std::make_unique<Application>("server_config.ini");
        app->start();
    }
    catch (const std::exception &e) {
        std::cout << e.what();
        
    }
    std::string line;
    std::getline(std::cin, line);
    _CrtDumpMemoryLeaks();
    return 0;
}
