#include "stdafx.h"
#include "App.h"
#include "CallbackMessage.h"
#include "Control.h"
#include "resource.h"
#include "Wnd.h"

class CCallbackDestroy : public ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        PostQuitMessage(0);
        return 0;
    }
};

class CCallbackPaint : public ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }
};

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

class CCallbackAbout : public ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        DialogBox(CApp::GetApp()->GetHinstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
        return 0;
    }
};

class CCallbackExit : public ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        DestroyWindow(hwnd);
        return 0;
    }
};

void CControl::AddCallbacks(
    CWnd * wnd
) {
    ICallbackMessage * cb = new CCallbackDestroy();
    m_callbacks.push_back(cb);
    wnd->AddCallbackWm(WM_DESTROY, cb);
    cb = new CCallbackPaint();
    m_callbacks.push_back(cb);
    wnd->AddCallbackWm(WM_PAINT, cb);
    cb = new CCallbackAbout();
    m_callbacks.push_back(cb);
    wnd->AddCallbackCmd(IDM_ABOUT, cb);
    cb = new CCallbackExit();
    m_callbacks.push_back(cb);
    wnd->AddCallbackCmd(IDM_EXIT, cb);
}
