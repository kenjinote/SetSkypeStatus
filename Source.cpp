#pragma comment(lib,"wtsapi32")
#pragma comment(lib,"psapi")

#include <windows.h>
#include <psapi.h>
#include <wtsapi32.h>

TCHAR szClassName[] = TEXT("SetSkypeStatus");

BOOL GetExeFilePathFromWindowHandle(HWND hWnd, LPTSTR lpszExePath, int szPathSize)
{
	DWORD dwProcessID = 0;
	GetWindowThreadProcessId(hWnd, &dwProcessID);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);
	if (!hProcess)
		return FALSE;
	HMODULE hModule = NULL;
	DWORD dwDummy = 0;
	if (!EnumProcessModules(hProcess, &hModule, sizeof(HMODULE), &dwDummy))
		return FALSE;
	if (!GetModuleFileNameEx(hProcess, hModule, lpszExePath, szPathSize))
		return FALSE;
	CloseHandle(hProcess);
	return TRUE;
}

BOOL IsSkypeWindow(HWND hWnd)
{
	TCHAR szModulePath[MAX_PATH] = { 0 };
	GetExeFilePathFromWindowHandle(hWnd, szModulePath, _countof(szModulePath));
	if (wcsstr(szModulePath, L"Skype.exe"))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK EnumWindowsProcForSkype(HWND hWnd, LPARAM lParam)
{
	TCHAR szWindowTitle[256];
	TCHAR szClassName[256];
	GetWindowText(hWnd, szWindowTitle, _countof(szWindowTitle));
	szWindowTitle[5] = 0;
	GetClassName(hWnd, szClassName, _countof(szClassName));
	if (lstrcmp(szWindowTitle, TEXT("Skype")) == 0 && lstrcmp(szClassName, TEXT("Chrome_WidgetWin_1")) == 0 && IsSkypeWindow(hWnd))
	{
		*((HWND*)lParam) = hWnd;
		return FALSE; // 列挙中止
	}
	return TRUE; // 列挙続行
}

BOOL CALLBACK EnumWindowsProcForSkypeTray(HWND hWnd, LPARAM lParam)
{
	TCHAR szClassName[256];
	GetClassName(hWnd, szClassName, _countof(szClassName));
	if (lstrcmp(szClassName, TEXT("Electron_NotifyIconHostWindow")) == 0 && IsSkypeWindow(hWnd))
	{
		*((HWND*)lParam) = hWnd;
		return FALSE; // 列挙中止
	}
	return TRUE; // 列挙続行
}

HWND GetSkypeWindow()
{
	HWND hSkypeWnd = NULL;
	EnumWindows(EnumWindowsProcForSkype, (LPARAM)&hSkypeWnd);
	return hSkypeWnd;
}

HWND GetSkypeTrayWindow()
{
	HWND hSkypeTrayWnd = NULL;
	EnumWindows(EnumWindowsProcForSkypeTray, (LPARAM)&hSkypeTrayWnd);
	return hSkypeTrayWnd;
}

VOID Login(LPCWSTR lpszStatusName)
{
	HWND hSkypeWnd = GetSkypeWindow();
	if (hSkypeWnd)
	{
		RECT rect;
		GetWindowRect(hSkypeWnd, &rect);
		int x = rect.left, y = rect.top;
		SetWindowPos(hSkypeWnd, 0, 9999, 0, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		SetForegroundWindow(hSkypeWnd);
		HWND hRenderWidgetWnd = FindWindowEx(hSkypeWnd, NULL, TEXT("Chrome_RenderWidgetHostHWND"), NULL);
		if (hRenderWidgetWnd == NULL)
		{
			HWND hTrayWnd = GetSkypeTrayWindow();
			if (hTrayWnd)
			{
				SendMessage(hTrayWnd, WM_USER + 31745, 0x3, 0x201);
			}
			Sleep(100);
			hRenderWidgetWnd = FindWindowEx(hSkypeWnd, NULL, TEXT("Chrome_RenderWidgetHostHWND"), NULL);
		}
		if (hRenderWidgetWnd)
		{
			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(1, 1));
			SendMessage(hRenderWidgetWnd, WM_LBUTTONUP, 0, MAKELPARAM(1, 1));

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_SPACE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_SPACE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			if (lpszStatusName)
			{
				LPCWSTR p = lpszStatusName;
				while (*p)
				{
					SendMessage(hRenderWidgetWnd, WM_CHAR, (WPARAM)*p, 0);
					p++;
				}
			}

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_SPACE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_SPACE, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_DOWN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_DOWN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_RETURN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_RETURN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(100);
		}
		SetWindowPos(hSkypeWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		SendMessage(hSkypeWnd, WM_CLOSE, 0, 0);
	}
}

VOID Logout()
{
	HWND hSkypeWnd = GetSkypeWindow();
	if (hSkypeWnd)
	{
		RECT rect;
		GetWindowRect(hSkypeWnd, &rect);
		int x = rect.left, y = rect.top;
		SetWindowPos(hSkypeWnd, 0, 9999, 0, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		SetForegroundWindow(hSkypeWnd);
		HWND hRenderWidgetWnd = FindWindowEx(hSkypeWnd, NULL, TEXT("Chrome_RenderWidgetHostHWND"), NULL);
		if (hRenderWidgetWnd == NULL)
		{
			HWND hTrayWnd = GetSkypeTrayWindow();
			if (hTrayWnd)
			{
				SendMessage(hTrayWnd, WM_USER + 31745, 0x3, 0x201);
			}
			Sleep(100);
			hRenderWidgetWnd = FindWindowEx(hSkypeWnd, NULL, TEXT("Chrome_RenderWidgetHostHWND"), NULL);
		}
		if (hRenderWidgetWnd)
		{
			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(1, 1));
			SendMessage(hRenderWidgetWnd, WM_LBUTTONUP, 0, MAKELPARAM(1, 1));

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_SPACE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_SPACE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_DELETE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_DELETE, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_TAB, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_SPACE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_SPACE, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_DOWN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_DOWN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_DOWN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_DOWN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_DOWN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_DOWN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_RETURN, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_RETURN, 0);

			Sleep(100);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(500);

			SendMessage(hRenderWidgetWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			SendMessage(hRenderWidgetWnd, WM_KEYUP, VK_ESCAPE, 0);

			Sleep(100);
		}
		SetWindowPos(hSkypeWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		SendMessage(hSkypeWnd, WM_CLOSE, 0, 0);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bLogined;
	static LONGLONG dwLastSessionChange;
	switch (msg)
	{
	case WM_CREATE:
		PostMessage(hWnd, WM_WTSSESSION_CHANGE, WTS_REMOTE_CONNECT, 0);
		WTSRegisterSessionNotification(hWnd, NOTIFY_FOR_ALL_SESSIONS);
		break;
	case WM_WTSSESSION_CHANGE:
		{
				if (GetTickCount64() - dwLastSessionChange <= 1000) // 前回の SSESSION CHANGE から 1 秒以内なら無視
				{
					return 0;
				}
				switch (wParam)
				{
				case WTS_REMOTE_CONNECT:
					{
						WCHAR szComputerName[MAX_PATH] = { 0 };
						PWTS_SESSION_INFO ppSessionInfo = 0;
						DWORD pCount;
						if (WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &ppSessionInfo, &pCount))
						{
							for (unsigned int i = 0; i<pCount; i++)
							{
								if (lstrcmp(ppSessionInfo[i].pWinStationName, TEXT("RDP-Tcp#0")) == 0)
								{
									DWORD bytesReturned = 0;
									LPWSTR pData = 0;
									if (WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, ppSessionInfo[i].SessionId, WTSClientName, &pData, &bytesReturned))
									{
										lstrcpyW(szComputerName, pData);
									}
									WTSFreeMemory(pData);
								}
							}
							WTSFreeMemory(ppSessionInfo);
						}
						if (bLogined == FALSE)
						{
							Login(szComputerName);
							bLogined = TRUE;
						}
					}
					break;
				case WTS_REMOTE_DISCONNECT:
					if (bLogined == TRUE)
					{
						Logout();
						bLogined = FALSE;
					}
					break;
				}
				dwLastSessionChange = GetTickCount64();
		}
		break;
	case WM_DESTROY:
		WTSUnRegisterSessionNotification(hWnd);
		if (bLogined == TRUE)
		{
			Logout();
			bLogined = FALSE;
		}
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	HANDLE hMutex = CreateMutex(NULL, FALSE, szClassName);
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		WNDCLASS wndclass = {
		0,
		WndProc,
		0,
		0,
		hInstance,
		0,
		0,
		0,
		0,
		szClassName
		};
		RegisterClass(&wndclass);
		HWND hWnd = CreateWindowEx(
			WS_EX_TOOLWINDOW,
			szClassName,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			hInstance,
			0
		);
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		ReleaseMutex(hMutex);
	}
	CloseHandle(hMutex);
	return (int)msg.wParam;
}
