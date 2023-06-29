#include "ConfigurationManager.h"
#include "../Log.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include "ConfigParser.h"
#include "../VERSION.hpp"


ConfigurationManager::ConfigurationManager()
{
    auto wd = std::filesystem::current_path();
    bool wdSet = false;
    
    if(!std::filesystem::exists(wd / "CostaBarcodes-Locations"))
    {
        LOG("Default Location doesn't exist, creating...");
        if(std::filesystem::create_directory(wd / "CostaBarcodes-Locations"))
        {
            LOG("Default location successfully created!");
            m_WorkingPath = (wd / "CostaBarcodes-Locations").string();
            wdSet = true;
        }
    }
    else
    {
        m_WorkingPath = (wd / "CostaBarcodes-Locations").string();
        wdSet = true;
    }

    if(wdSet)
    {
        if(!std::filesystem::exists(m_WorkingPath + "/config.json"))
        {
            LOG("Config file doesn't exist, creating...");
            auto cf = std::ofstream(m_WorkingPath + "/config.json");
            if(std::filesystem::exists(m_WorkingPath + "/config.json"))
            {
                LOG("Config File successfully created!");
                CreateDefaultConfig(cf);
                cf.close();
                m_IsReady = true;
            }
        }
        else
        {
            m_ConfigPath = m_WorkingPath + "/config.json";
            if(LoadConfigFile())
            {
                LOG("Config loaded successfully!");
                m_IsReady = true;
            }
        }
    }
}

void ConfigurationManager::CreateDefaultConfig(std::ofstream& configFile)
{
    m_configuration = Configuration(atoi(CB_MAJOR_VERSION), atoi(CB_MINOR_VERSION), m_WorkingPath + "/images", m_WorkingPath + "/locations.json", m_WorkingPath + "/output");

    ConfigParser::SaveConfig(m_configuration, configFile);
}

bool ConfigurationManager::LoadConfigFile()
{
    
    if(m_WorkingPath.empty() || m_ConfigPath.empty()) { return false; }

    std::ifstream file(m_ConfigPath);

    ConfigParser::LoadConfig(m_configuration, file);
    
    file.close();
    
    return true;
}


