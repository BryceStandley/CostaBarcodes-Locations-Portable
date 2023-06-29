#pragma once
#include <string>
#include <map>
#include "Location.h"

class LocationManager
{
public:

    static LocationManager& Get() { static LocationManager INSTANCE; return INSTANCE; }

    std::map<std::string, Location>& GetLocationStore() { return m_Locations; }


    bool IsReady() const { return m_IsReady; }
    
    bool Init(const std::string& locationStorePath);

    


private:
    LocationManager();
    
    bool CreateDefaultLocations();

    bool LoadLocationConfig(const std::string& locationConfigPath);

    std::map<std::string, Location> m_Locations;

    bool m_IsReady = false;
};
