#ifndef ADAPTER_HANDLER_HPP
#define ADAPTER_HANDLER_HPP

#include <memory>

#include <Wbemidl.h>
#include <comdef.h>

#include "adapter_settings.hpp"
namespace ncmanager
{

class AdapterHandler
{
public:
    AdapterHandler();
    AdapterSettings getSettings();
    bool setSettings(const AdapterSettings& settings);
private:
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    
}; // class AdapterHandler

}; // namespace ncmanager
#endif