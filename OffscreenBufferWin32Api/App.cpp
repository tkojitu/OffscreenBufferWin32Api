#include "stdafx.h"
#include "App.h"
#include "resource.h"

CApp * CApp::GetApp(
) {
    CApp * s_app = nullptr;

    if (s_app)
        return s_app;
    s_app = new CApp();
    return s_app;
}

CApp::CApp(
) {
}

CApp::~CApp(
) {
}

bool CApp::InitInstance(
    HINSTANCE instance,
    int cmdshow
) {
    m_instance = instance;
    LoadString(instance, IDS_APP_TITLE, m_title, MAX_LOADSTRING);
    LoadString(instance, IDC_OFFSCREENBUFFERWIN32API, m_window_class, MAX_LOADSTRING);
    MyRegisterClass(instance);
    HWND hwnd = CreateWindowW(m_window_class, m_title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, instance, nullptr);
    if (!hwnd) {
        return false;
    }
    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);
    return true;
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

ATOM CApp::MyRegisterClass(
    HINSTANCE hInstance
) {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OFFSCREENBUFFERWIN32API));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_OFFSCREENBUFFERWIN32API);
    wcex.lpszClassName = m_window_class;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

HINSTANCE CApp::GetHinstance(
) {
    return m_instance;
}
