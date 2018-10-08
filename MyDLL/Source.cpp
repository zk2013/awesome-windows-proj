#include <Windows.h>

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	while (1) {
		OutputDebugString(L"onload");
		Sleep(2000);
	}

	return 0;
}

void on_load() {
	
	DWORD dwThreadId;
	CloseHandle(CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadFunction,       // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId));   // returns the thread identifier );
}

void on_unload() {
	OutputDebugString(L"on_unload");
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lParam)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//MessageBox(NULL, L"DLL Injected", L"Kernel Injector", MB_ICONINFORMATION);
		on_load();
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, L"DLL Detached from process", L"Kernel Injector", MB_ICONINFORMATION);
		on_unload();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	default:
		break;
	}

	return TRUE;
}