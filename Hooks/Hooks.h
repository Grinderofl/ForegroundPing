// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HOOKS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HOOKS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HOOKS_EXPORTS
#define HOOKS_API __declspec(dllexport)
#else
#define HOOKS_API __declspec(dllimport)
#endif

// This class is exported from the Hooks.dll
class HOOKS_API CHooks {
public:
	CHooks(void);
	bool Install(HWND notify);
	bool Uninstall();
};

extern HOOKS_API int nHooks;

HOOKS_API int fnHooks(void);
