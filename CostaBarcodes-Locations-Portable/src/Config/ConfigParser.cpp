#include "ConfigParser.h"

#include <iostream>


bool ConfigParser::SaveConfig(const Configuration& config, std::ostream& out)
{
    std::string image = config.GetImageStorePath();
    std::string location = config.GetLocationStorePath();
    std::string output = config.GetOutputPath();

    Replace_All(image, "\\", "/");
    Replace_All(location, "\\", "/");
    Replace_All(output, "\\", "/");
    
    std::stringstream ss;
    ss << "{\n";
    ss << "\t\"version\" : \n";
    ss << "\t\t{\n";
    ss << "\t\t\t\"major\" : \"" << config.GetMajorVersion() << "\",\n";
    ss << "\t\t\t\"minor\" : \"" << config.GetMinorVersion() << "\"\n";
    ss << "\t\t},\n";
    ss << "\t\"imageStore\" : \"" << image << "\",\n";
    ss << "\t\"locationStore\" : \"" << location << "\",\n";
    ss << "\t\"output\" : \"" << output << "\"\n";
    ss << "}";

    out << ss.rdbuf();

    return true;
}

bool ConfigParser::LoadConfig(Configuration& config, std::istream& in)
{
    std::string major;
    std::string minor;
    std::string image;
    std::string location;
    std::string output;
    
    std::stringstream ss;

    ss << in.rdbuf();
    std::string s = ss.str();

    auto mjfind = "\"major\" : \"";
    auto mjoff = s.find(mjfind);
    major = s.substr(mjoff + std::strlen(mjfind), (s.find("\",\n", mjoff) - (mjoff + std::strlen(mjfind))));

    auto mifind = "\"minor\" : \"";
    auto mioff = s.find(mifind);
    minor = s.substr(mioff + std::strlen(mifind), (s.find("\",\n", mioff) - (mioff + std::strlen(mifind))));
    
    auto ifind = "\"imageStore\" : \"";
    auto ioff = s.find(ifind);
    image = s.substr(ioff + std::strlen(ifind), (s.find("\",\n", ioff) - (ioff + std::strlen(ifind))));

    auto lfind = "\"locationStore\" : \"";
    auto loff = s.find(lfind);
    location = s.substr(loff + std::strlen(lfind), (s.find("\",\n", loff) - (loff + std::strlen(lfind))));

    auto ofind = "\"output\" : \"";
    auto ooff = s.find(ofind);
    output = s.substr(ooff + std::strlen(ofind), (s.find("\"\n", ooff) - (ooff + std::strlen(ofind))));

    config = Configuration(atoi(major.c_str()), atoi(minor.c_str()), image, location, output);
    
    return true;
}

