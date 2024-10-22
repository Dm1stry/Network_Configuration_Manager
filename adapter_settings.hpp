#ifndef ADAPTER_SETTINGS_HPP
#define ADAPTER_SETTINGS_HPP

#include <string>

#include "adapter_handler.hpp"

namespace ncmanager
{

class AdapterSettings
{
public:
    bool saveToFile(std::string filename);
    bool loadFromFile(std::string filename);

    std::string name;
}; // class AdapterSettings

}; // namespace ncmanager

#endif