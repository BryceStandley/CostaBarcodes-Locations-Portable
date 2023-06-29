#pragma once
#include <string>
/**
 * \brief Defines the structure for storing config data
 */
class Configuration
{
public:
    Configuration() {}
    Configuration(int major, int minor, const std::string& imageStore, const std::string& locationStore, const std::string& output);

    int GetMajorVersion() const { return m_MajorVersion; }
    int GetMinorVersion() const { return m_MinorVersion; }
    std::string GetVersion() const { return std::string(std::to_string(m_MajorVersion) + "." + std::to_string(m_MinorVersion)); }
    std::string GetImageStorePath() const { return m_ImageStorePath; }
    std::string GetLocationStorePath() const { return m_LocationStorePath; }
    std::string GetOutputPath() const { return m_OutputPath; }
    
private:
    
    int m_MajorVersion = -1;
    int m_MinorVersion = -1;
    std::string m_ImageStorePath;
    std::string m_LocationStorePath;
    std::string m_OutputPath;
    
};
