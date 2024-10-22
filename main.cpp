#include <Windows.h>
#include <Netcfgx.h>
#include <iostream>
#include <comutil.h>
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "netcfgx.lib")

HRESULT GetNetCfg(INetCfg **ppNetCfg, INetCfgLock **ppLock) {
    HRESULT hr;
    INetCfg *pNetCfg = NULL;
    INetCfgLock *pLock = NULL;

    hr = CoCreateInstance(CLSID_CNetCfg, NULL, CLSCTX_INPROC_SERVER, IID_INetCfg, (void**)&pNetCfg);
    if (SUCCEEDED(hr)) {
        hr = pNetCfg->QueryInterface(IID_INetCfgLock, (void**)&pLock);
        if (SUCCEEDED(hr)) {
            hr = pLock->AcquireWriteLock(5000, L"IPv6 Configuration", NULL);
            if (SUCCEEDED(hr)) {
                hr = pNetCfg->Initialize(NULL);
                if (SUCCEEDED(hr)) {
                    *ppNetCfg = pNetCfg;
                    *ppLock = pLock;
                }
            }
        }
    }
    return hr;
}

HRESULT InstallOrUninstallIPv6(BOOL bEnable) {
    INetCfg *pNetCfg = NULL;
    INetCfgLock *pLock = NULL;
    HRESULT hr = GetNetCfg(&pNetCfg, &pLock);

    if (SUCCEEDED(hr)) {
        INetCfgClass *pNetCfgClass = NULL;
        INetCfgComponent *pComponent = NULL;
        INetCfgClassSetup *pSetup = NULL;

        // Retrieve the class object for protocol components
        hr = pNetCfg->QueryNetCfgClass(&GUID_DEVCLASS_NETTRANS, IID_INetCfgClass, (void**)&pNetCfgClass);
        if (SUCCEEDED(hr)) {
            hr = pNetCfgClass->QueryInterface(IID_INetCfgClassSetup, (void**)&pSetup);
            if (SUCCEEDED(hr)) {
                // Find the IPv6 protocol component
                hr = pNetCfg->FindComponent(L"ms_tcpip6", &pComponent);
                if (SUCCEEDED(hr)) {
                    // If we found the IPv6 component and need to disable it
                    if (!bEnable) {
                        // Uninstall the component
                        hr = pSetup->DeInstall(pComponent, NULL, NULL);
                        if (SUCCEEDED(hr)) {
                            std::wcout << L"IPv6 has been disabled." << std::endl;
                        } else {
                            std::wcout << L"Failed to disable IPv6." << std::endl;
                        }
                    } else {
                        std::wcout << L"IPv6 is already installed/enabled." << std::endl;
                    }
                } else if (bEnable) {
                    // If IPv6 is not found and we need to enable it, install it
                    OBO_TOKEN token;
                    ZeroMemory(&token, sizeof(OBO_TOKEN));
                    token.Type = OBO_USER;

                    hr = pSetup->Install(L"ms_tcpip6", &token, 0, 0, NULL, NULL);
                    if (SUCCEEDED(hr)) {
                        std::wcout << L"IPv6 has been enabled." << std::endl;
                    } else {
                        std::wcout << L"Failed to enable IPv6." << std::endl;
                    }
                }
                pSetup->Release();
            }
            pNetCfgClass->Release();
        }

        // Apply the changes and release the lock
        if (pNetCfg) {
            pNetCfg->Apply();
            pNetCfg->Uninitialize();
            pNetCfg->Release();
        }
        if (pLock) {
            pLock->ReleaseWriteLock();
            pLock->Release();
        }
    }
    return hr;
}

int main() {
    CoInitialize(NULL);

    // Disable IPv6
    HRESULT hr = InstallOrUninstallIPv6(FALSE);
    if (FAILED(hr)) {
        std::wcout << L"Failed to disable IPv6." << std::endl;
    }

    // Enable IPv6 (just to demonstrate both)
    hr = InstallOrUninstallIPv6(TRUE);
    if (FAILED(hr)) {
        std::wcout << L"Failed to enable IPv6." << std::endl;
    }

    CoUninitialize();
    return 0;
}
