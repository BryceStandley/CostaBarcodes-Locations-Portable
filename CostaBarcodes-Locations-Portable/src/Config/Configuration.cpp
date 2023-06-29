#include "Configuration.h"

Configuration::Configuration(int major, int minor, const std::string& imageStore, const std::string& locationStore, const std::string& output)
    : m_MajorVersion(major), m_MinorVersion(minor), m_ImageStorePath(imageStore), m_LocationStorePath(locationStore), m_OutputPath(output)
{}
