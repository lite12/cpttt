#include "stdafx.h"

#include "include/UserStore.h"
#include "shared/include/Logger.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "pugixml.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace ServerApp {
	std::shared_ptr<UserDefinition> UserStore::createUserFromXml(const pugi::xml_node &node)
	{
		auto userDef = std::make_shared<UserDefinition>();
		userDef->email = node.attribute("mail").value();
		userDef->key = node.attribute("key").value();
		for (const auto& alert : node.children()) {
			std::string alertValue = alert.attribute("limit").value();
			boost::erase_all(alertValue, "%");
			try {
				int alertIntValue = boost::lexical_cast<int>(alertValue);
				userDef->alerts[alert.attribute("type").value()] = alertIntValue;
			}
			catch (const std::exception& e) {
				std::string error = (boost::format("Invalid limit definition for user <%s>") % userDef->email).str();
				throw std::exception(error.c_str());
			}
		}
		return userDef;
	}
	std::shared_ptr<UserDefinition> UserStore::getUserViaKey(const std::string &key) const
	{
		if (m_users.find(key) == m_users.end())
			return nullptr;
		return m_users.at(key);
	}

	UserStore::UserStore(const std::string &userFile)
	{

		pugi::xml_document doc;


		pugi::xml_parse_result result = doc.load_file(userFile.c_str());
		if (result.status == pugi::xml_parse_status::status_file_not_found)
			throw std::exception("Unable to find user definition file");
		if (result.status != pugi::xml_parse_status::status_ok)
			throw std::exception("Unable to parse user definition file");
		for (const auto& user : doc.children()) {
			auto userDef = createUserFromXml(user);
			if (userDef->email.empty() || userDef->key.empty())
				throw std::exception("Invalid user definition!");
			if (m_users.find(userDef->key) != m_users.end()) {
				throw std::exception("Multipe user with same key!");
			}
			m_users[userDef->key] = userDef;
		}
	}
}