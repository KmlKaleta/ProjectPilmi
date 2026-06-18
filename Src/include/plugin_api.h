//
// Created by Kamil on 18.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_PLUGIN_API_H
#define SHEEP_GOES_DEVILE_PLUGIN_API_H

#ifdef _WIN32
#  define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#  define DLL_EXPORT extern "C"
#endif

struct PluginState {
    int counter;
};

using InitFn = void(*)(PluginState*);
using UpdateFn = void(*)(PluginState*);
using ShutdownFn = void(*)(PluginState*);

struct PluginAPI {
    InitFn init;
    UpdateFn update;
    ShutdownFn shutdown;
};

DLL_EXPORT PluginAPI GetPluginAPI();

#endif //SHEEP_GOES_DEVILE_PLUGIN_API_H
