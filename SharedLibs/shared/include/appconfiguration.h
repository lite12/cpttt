#pragma once
#include <string>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
namespace SharedLibs {
	using configSection = std::unordered_map<std::string, std::string>;

	class AppConfiguration
	{

		configSection readConfigSection(boost::property_tree::basic_ptree<std::string, std::string> section);
		/// INI file sections
		std::unordered_map<std::string, configSection> m_sections;


	public:
		configSection get(std::string sectionName) {
			return m_sections[sectionName];
		}
        AppConfiguration() {};
		explicit AppConfiguration(const char* fileName);
		~AppConfiguration();

	};
}
