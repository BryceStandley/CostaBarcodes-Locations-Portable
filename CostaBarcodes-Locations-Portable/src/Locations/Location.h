#pragma once
#include <string>
#include <algorithm>

/**
 * \brief Structure of a Location and its data
 */
class Location
{
public:
    enum LocationType { ACTIVE, RESERVE };
    
    Location(std::string isle, int position, int level, LocationType locationType);

    std::string GetName() { return m_Name; }

    std::string GetIsle() { return m_Isle; }

    int GetPosition() const { return m_Position; }
    std::string GetPositionAsString() { return GetAsString(m_Position); }

    int GetLevel() const { return m_Level; }
    std::string GetLevelAsString() { return GetAsString(m_Level); }

    LocationType GetLocationType() const { return m_LocationType; }

    
private:

    std::string GetAsString(int val);
    
    std::string m_Name;

    std::string m_Isle = "AA";

    int m_Position = 1;

    int m_Level = 1;

    LocationType m_LocationType = RESERVE;
};
