#include <Windows.h>
#include <ctime>

#define POINT_STEP 50
#define SIZE_STEP 100
#define SIZE 3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hIst,
	HINSTANCE prevIst, //
	LPSTR cmdArgs,
	int typeShow) {

	srand(time(NULL));
	WNDCLASS wndclass;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hIst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndclass.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = TEXT("MyClass");
	wndclass.lpszClassName = L"MyClass";
	wndclass.style = NULL;
	wndclass.lpfnWndProc = WndProc;

	RegisterClass(&wndclass);

	HWND hwnds[SIZE];
	hwnds[0] = CreateWindow(
		L"MyClass",
		L"WinApp",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		500, 400,
		NULL,
		NULL,
		hIst,
		NULL);

	int size = 100;

	for (size_t i = 1; i < SIZE; i++)
	{
		hwnds[i] = CreateWindow(
			L"MyClass",
			L"WinApp",
			WS_CLIPCHILDREN,
			100 + (i * POINT_STEP), size + (i + POINT_STEP),
			500 - (i * SIZE_STEP), 400 - (i * SIZE_STEP),
			hwnds[i - 1],
			NULL,
			hIst,
			NULL);

		size = size + (i * 50);
	}


	for (size_t i = 0; i < SIZE; i++)
	{
		int red = rand() % 256;
		int green = rand() % 256;
		int blue = rand() % 256;

		SetClassLong(hwnds[i], GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(red, green, blue)));

		ShowWindow(hwnds[i], typeShow);
		UpdateWindow(hwnds[i]);
	}

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) == TRUE) {
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return TRUE;
}
