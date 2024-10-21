#include "stdafx.h"
#include "App.h"
#include "CallbackMessage.h"
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

LRESULT CWnd::WindowProcedure(
    HWND hwnd,
    UINT message,
    WPARAM wparam,
    LPARAM lparam
) {
    if (message == WM_COMMAND) {
        int wmid = LOWORD(wparam);
        if (m_callback_cmds.count(wmid))
            return m_callback_cmds[wmid]->HandleMessage(hwnd, message, wparam, lparam);
    } else if (m_callback_wms.count(message)) {
        return m_callback_wms[message]->HandleMessage(hwnd, message, wparam, lparam);
    }
    return DefWindowProc(hwnd, message, wparam, lparam);
}

static LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT message,
    WPARAM wparam,
    LPARAM lparam
) {
    if (CApp::GetApp()->GetWnd())
        return CApp::GetApp()->GetWnd()->WindowProcedure(hwnd, message, wparam, lparam);
    return DefWindowProc(hwnd, message, wparam, lparam);
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

void CWnd::AddCallbackWm(
    UINT message,
    ICallbackMessage * callback
) {
    m_callback_wms[message] = callback;
}

void CWnd::AddCallbackCmd(
    UINT wmid,
    ICallbackMessage * callback
) {
    m_callback_cmds[wmid] = callback;
}
