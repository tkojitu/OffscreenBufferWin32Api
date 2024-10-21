#include "stdafx.h"
#include "App.h"
#include "resource.h"
#include "Wnd.h"

CWnd::CWnd(
    CApp * app
) : m_app(app) {
}

CWnd::~CWnd(
) {
}

bool CWnd::Init(
) {
    MyRegisterClass();
    m_hwnd = CreateWindowW(m_app->GetWindowClass(), m_app->GetTitle(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_app->GetHinstance(), nullptr);
    return m_hwnd != nullptr;
}

static INT_PTR CALLBACK About(
    HWND dlg,
    UINT message,
    WPARAM wparam,
    LPARAM lparam
) {
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wparam) == IDOK || LOWORD(wparam) == IDCANCEL) {
            EndDialog(dlg, LOWORD(wparam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

static LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (message) {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(CApp::GetApp()->GetHinstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM CWnd::MyRegisterClass(
) {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_app->GetHinstance();
    wcex.hIcon = LoadIcon(m_app->GetHinstance(), MAKEINTRESOURCE(m_app->GetIdIcon()));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(m_app->GetIdMenu());
    wcex.lpszClassName = m_app->GetWindowClass();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

bool CWnd::Show(
    int cmdshow
) {
    if (!m_hwnd)
        return false;
    return ::ShowWindow(m_hwnd, cmdshow);
}

bool CWnd::Update(
) {
    if (!m_hwnd)
        return false;
    return ::UpdateWindow(m_hwnd);
}
