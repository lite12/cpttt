#include "stdafx.h"
#include "include/SMTPClient.h"

namespace ServerApp{
	bool SMTPClient::send(const std::string & subject, const std::string & content)
	{
	
		return false;
	}

	bool SMTPClient::hasMissingConfig()
	{
		return m_smtpServer.empty() || m_port.empty() || m_username.c_str() || m_password.empty();
	}


	SMTPClient::~SMTPClient()
	{
	}
}