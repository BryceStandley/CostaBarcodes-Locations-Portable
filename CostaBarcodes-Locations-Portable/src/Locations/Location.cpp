#include "Location.h"

Location::Location(std::string isle, int position, int level, LocationType locationType)
    :m_Position(position), m_Level(level), m_LocationType(locationType)
{
    std::transform(isle.begin(), isle.end(), isle.begin(), ::toupper);
    m_Isle = isle;

    m_Name = m_Isle + GetPositionAsString() + GetLevelAsString();
}

std::string Location::GetAsString(int val)
{
    if(val < 10)
    {
        return std::string("0" + std::to_string(val));
    }

    return std::to_string(val);
}


