#ifndef __MAGE_PLUGIN_H__
#define __MAGE_PLUGIN_H__

#ifdef WIN32
# include <windows.h>
# define EXPORT __declspec(dllexport)
#else
# define EXPORT
#endif

extern "C"
{

EXPORT void StartPlugin();
EXPORT void EndPlugin();

}
#endif/*__MAGE_PLUGIN_H__*/