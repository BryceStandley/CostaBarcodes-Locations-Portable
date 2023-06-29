#pragma once
#include <string>

#include "Configuration.h"


class ConfigurationManager
{
public:

    bool IsReady() const { return m_IsReady; }
    
    std::string GetWorkingDirectory() const { return m_WorkingPath; }
    std::string GetConfigFilePath() const { return m_ConfigPath; }
    Configuration GetConfig() const { return m_configuration; }

    
    // Instance Setup
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator= (const ConfigurationManager& ) = delete;
    ConfigurationManager(ConfigurationManager&&) = delete;
    ConfigurationManager& operator=(ConfigurationManager&&) = delete;
    
    static auto& Get()
    {
        static ConfigurationManager INSTANCE;
        return INSTANCE;
    }

    
private:
    ConfigurationManager();

    void CreateDefaultConfig(std::ofstream& configFile);
    bool LoadConfigFile();

    std::string m_WorkingPath;

    std::string m_ConfigPath;

    Configuration m_configuration;

    bool m_IsReady = false;
};
