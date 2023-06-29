#include "LocationManager.h"

LocationManager::LocationManager() {}


bool LocationManager::Init(const std::string& locationStorePath)
{
    //TODO: Load or create default locations

    m_IsReady = true;
    return true;
}

bool LocationManager::CreateDefaultLocations()
{
    return true;
}

bool LocationManager::LoadLocationConfig(const std::string& locationConfigPath)
{
    return true;
}



