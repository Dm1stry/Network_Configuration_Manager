#include "adapter_handler.hpp"

using AdapterHandler = ncmanager::AdapterHandler;
using AdapterSettings = ncmanager::AdapterSettings;

AdapterHandler::AdapterHandler()
{
    HRESULT hres;

    //TODO: Add raise exception system 
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);

    hres = CoInitializeSecurity(NULL, -1, NULL, NULL, 
                                RPC_C_AUTHN_LEVEL_DEFAULT, 
                                RPC_C_IMP_LEVEL_IMPERSONATE, 
                                NULL, EOAC_NONE, NULL);

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, 
                            IID_IWbemLocator, (LPVOID *)&pLoc);

    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);


}

AdapterSettings AdapterHandler::getSettings()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    HRESULT hres = pSvc->ExecQuery(
        bstr_t("WQL"), 
        bstr_t("SELECT * FROM Win32_NetworkAdapterConfiguration WHERE Index=X"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
        NULL, 
        &pEnumerator
    );

    

    
    return AdapterSettings();
}

bool AdapterHandler::setSettings(const AdapterSettings& settings)
{
    return true;
}