#pragma once

#include "Util.h"
#define ReleaseCOM(x) {if(x) x->Release();}

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE *pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	BaseWindow() : m_hwnd(NULL) { }

	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName();

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(
			dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return (m_hwnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hwnd; }

protected:

	virtual PCWSTR  ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};

class Direct2d {
public:

	Direct2d() :
		pFactory(NULL), 
		pRenderTarget(NULL),
		pBlackBrush(NULL), 
		pRect(NULL), 
		pRound(NULL){}

	~Direct2d() {
		ReleaseCOM(pRenderTarget);
		ReleaseCOM(pFactory);
		ReleaseCOM(pBlackBrush);
		ReleaseCOM(pRect);
		ReleaseCOM(pRound);
	}

	bool Init(HWND hwnd) {
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&pFactory
		);
		if (FAILED(hr)) return 0;
		GetClientRect(hwnd, &rect);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd, 
				D2D1::SizeU(
					rect.right - rect.left,
					rect.bottom - rect.top
				)
			),
			&pRenderTarget
		);
		if (FAILED(hr)) return 0; 
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
		if (FAILED(hr)) return 0; 
		return 1;
	}

	void DrawRectangle(FXMVECTOR _point, FXMVECTOR _offset) {
		XMFLOAT2 point; 
		XMFLOAT2 rect; 
		XMStoreFloat2(&point, _point);
		XMStoreFloat2(&rect, _offset); 
		HRESULT hr; 
		hr = pFactory->CreateRectangleGeometry(
			D2D1::RectF(point.x, point.y, point.x + rect.x, point.y + rect.y), 
			&pRect
		);
		if (FAILED(hr)) return; 
		pRenderTarget->DrawGeometry(pRect, pBlackBrush);
		ReleaseCOM(pRect);
	}
		
	void DrawRound(FXMVECTOR _point, float radius) {
		XMFLOAT2 origin;
		XMStoreFloat2(&origin, _point);
		HRESULT hr; 
		hr = pFactory->CreateEllipseGeometry(
			D2D1::Ellipse(D2D1::Point2F(origin.x, origin.y), radius, radius),
			&pRound
		);
		if (FAILED(hr)) return;
		pRenderTarget->DrawGeometry(pRound, pBlackBrush);
		ReleaseCOM(pRound);
	}

	void Begin() {
		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}

	void End() {
		pRenderTarget->EndDraw();
	}

protected:
	ID2D1Factory* pFactory; 
	ID2D1HwndRenderTarget* pRenderTarget; 
	ID2D1SolidColorBrush* pBlackBrush;	
	ID2D1RectangleGeometry* pRect; 
	ID2D1EllipseGeometry* pRound; 
	RECT rect; 
};