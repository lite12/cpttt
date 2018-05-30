/**
* @author Ahmet Emir Ercin
* @date  26 Sep 2017
*/
#pragma once

#include <string>
#include "shared/include/AppConfiguration.h"

namespace ServerApp {
	class SMTPClient
	{
		std::string m_smtpServer;
		std::string m_port;
		std::string m_username;
		std::string m_password;
		std::string m_from;
	public:
		bool send(const std::string& subject, const std::string& content);
		bool hasMissingConfig();
		SMTPClient(SharedLibs::configSection config) :m_smtpServer(config["server"]),
			m_port(config["port"]),
			m_from(config["from"]),
			m_username(config["username"]),
			m_password(config["password"]) {};
		~SMTPClient();
	};
}