#pragma once
#include "Configuration.h"
#include <sstream>
#include "../Utils.hpp"
#include "../Log.h"

/**
 * \brief Processes data in or out to the config file. Note this is a really bad way to do this
 */
class ConfigParser
{
public:
 static bool SaveConfig(const Configuration& config, std::ostream& out);

 static bool LoadConfig(Configuration& config, std::istream& in);
};
