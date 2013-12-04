#define STRICT
#include <windows.h>
#include <mmsystem.h>

HWND hWnd;
HRGN holeRgn;
int current;
bool pending = false;
bool fresh = false; 
short direction = 1;
int duration = 100;
int currentStep = 0;
int counter = 0;
int target = 20;

DWORD WINAPI ThreadProc()
{
	while (true || counter >= 50000)
	{
		if (fresh)
		{
			fresh = false;
			pending = true;
			direction = 1;
			current = 0;
			currentStep = 0;
		}

		if (direction == 1)
			current = currentStep;
		else
			current = target - (currentStep - target);

				SetLayeredWindowAttributes(hWnd, 0, (255 * current) / 100, LWA_ALPHA);
		
		if (direction == -1 && current == 0) {
			pending = false;
			return 0;
		}
		if (direction == 1 && current >= target)
			direction = -1;

		currentStep++;

		Sleep(duration / target);
		counter++;
	}
	return 0;
}

void CALLBACK WinEventProc(
	HWINEVENTHOOK hWinEventHook,
	DWORD event,
	HWND hwnd,
	LONG idObject,
	LONG idChild,
	DWORD dwEventThread,
	DWORD dwmsEventTime
	)
{
	if (hwnd &&
		idObject == OBJID_WINDOW &&
		idChild == CHILDID_SELF &&
		event == EVENT_SYSTEM_FOREGROUND) {
		fresh = true;
		if (pending)
			return;
		else
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, NULL, 0, NULL);
		/*PlaySound(TEXT("C:\\Windows\\Media\\Speech Misrecognition.wav"),
			NULL, SND_FILENAME | SND_ASYNC);*/
	}
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev,
	LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX winclass;
	LPCWSTR className = L"windowClass";

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS;
	winclass.lpfnWndProc = &WndProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinst;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = className;
	winclass.hIconSm = NULL;
	
	if (!RegisterClassEx(&winclass))
	{
		MessageBox(NULL, L"Failed registering wndclass", L"Error", MB_ICONERROR | MB_OK);
		return 0;
	}

	
	hWnd = CreateWindowEx(WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW, className, L"Window", WS_OVERLAPPED | WS_POPUP, CW_USEDEFAULT | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST, 0, 300, 200, NULL, NULL, hinst, NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, L"Failed to create window", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);

	HRGN windowRgn;
	HRGN thisRgn;
	holeRgn = CreateRectRgn(0, 0, 0, 0);
	windowRgn = CreateRectRgn(0, 0, windowRect.right, windowRect.bottom);
	thisRgn = CreateRectRgn(50, 50, windowRect.right - 50, windowRect.bottom - 50);
	CombineRgn(holeRgn, thisRgn, windowRgn, RGN_XOR);
	SetWindowRgn(hWnd, holeRgn, TRUE);
	
	// Transparency
	SetWindowLong(hWnd, GWL_EXSTYLE,
	GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Cut out box
	SetLayeredWindowAttributes(hWnd, 0, (255 * 0) / 100, LWA_ALPHA);

	HWINEVENTHOOK hWinEventHook = SetWinEventHook(
		EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
		NULL, WinEventProc, 0, 0,
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (hWinEventHook) UnhookWinEvent(hWinEventHook);
	return 0;
}