// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "include/Application.h"

using namespace ClientApp;

int main() {
    std::unique_ptr<Application> app;
    try {
        app = std::make_unique<Application>("client_config.ini");
        app->start();
    }
    catch (const std::exception &e) {

        std::cout << e.what() << std::endl;
        std::cout << "Press Ctrl+C to exit...";
    }

    std::string line;
    std::getline(std::cin, line);
    return 0;
}

