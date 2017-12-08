#include "WinClass.h"
#include "GameTimer.h"
#include "Unit.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR  ClassName() const { return L"Game Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
	}
	return 0;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}

class Main {
public:
	Main() {
		width = 900;
		height = 900;
	}
	~Main() {}

	bool Init(int nCmdShow) {
		if (!win.Create(L"Steering Behaviour", WS_OVERLAPPEDWINDOW, 0, CW_USEDEFAULT, CW_USEDEFAULT, width, height))
		{
			return 0;
		}

		ShowWindow(win.Window(), nCmdShow);

		if (!canvas.Init(win.Window())) {
			MessageBox(NULL, L"Canvas Error!", 0, 0);
			return 0; 
		}
		return 1; 
	}

	void Update() {}
	void Render();

private:
	MainWindow win;
	Direct2d canvas;
	int width; 
	int height; 
};

void Main::Render() {
	canvas.Begin();
	XMVECTOR b; 
	XMFLOAT2 a; 
	a.x = 100; 
	a.y = 100; 
	a = a + a; 
	b = XMLoadFloat2(&a);
	canvas.DrawRectangle(b, b);
	canvas.End();
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	Main main;
	if (!main.Init(nCmdShow)) return 0; 
	
	MSG msg = {};
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			main.Update();
			main.Render();
		}
	}

	return 0;
}
