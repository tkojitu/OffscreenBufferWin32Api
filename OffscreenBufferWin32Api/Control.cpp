#include "stdafx.h"
#include "App.h"
#include "CallbackMessage.h"
#include "CallbackTimer.h"
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
    CCallbackPaint(CWnd * wnd) : m_wnd(wnd) {}
    virtual ~CCallbackPaint() {}

    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        DrawRect(dc);
        const wchar_t * msg = L"hello, world";
        RECT r = { 100, 100, 200, 200 };
        DrawText(dc, msg, wcslen(msg), &r, DT_CENTER);
        EndPaint(hwnd, &ps);
        return 0;
    }

    virtual void DrawRect(HDC dc) {
        if (!m_wnd->GetHwnd())
            return;
        HDC buf = ::CreateCompatibleDC(dc);
        RECT rect = m_wnd->GetClientRect();
        HBITMAP bm = ::CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
        HBITMAP saved_bm = (HBITMAP)SelectObject(buf, bm);
        {
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(buf, &rect, white);
            HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
            FillRect(buf, &m_rect, red);
            BitBlt(dc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, buf, 0, 0, SRCCOPY);
            DeleteObject(red);
            DeleteObject(white);
        }
        SelectObject(buf, saved_bm);
        DeleteObject(bm);
        DeleteObject(buf);
    }

    virtual void MoveRect() {
        RECT rect = m_wnd->GetClientRect();
        OffsetRect(&m_rect, 1, 1);
        if (m_rect.top > rect.bottom) {
            int h = m_rect.bottom - m_rect.top;
            m_rect.top = 0;
            m_rect.bottom = h;
        }
        if (m_rect.left > rect.right) {
            int w = m_rect.right - m_rect.left;
            m_rect.left = 0;
            m_rect.right = w;
        }
        m_wnd->InvalidateRect(rect, false);
        m_wnd->Update();
    }

private:
    RECT m_rect = { 0, 0, 10, 10 };
    CWnd * m_wnd = nullptr;
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

class CCallbackErasebkgnd : public ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        return 0;
    }
};

class CCallbackTimer : public ICallbackTimer {
public:
    CCallbackTimer(CWnd * wnd, CCallbackPaint * paint) : m_wnd(wnd), m_paint(paint) {}
    virtual ~CCallbackTimer() {}

    virtual void OnTimer(HWND hwnd, UINT param2, UINT_PTR param3, DWORD param4) {
        m_paint->MoveRect();
    }

    virtual void Start() {
        if (m_started)
            return;
        m_started = true;
        m_wnd->SetTimer(this, 33);
    }

    virtual void End() {
        if (!m_started)
            return;
        m_started = false;
        m_wnd->KillTimer(this);
    }

    virtual void Toggle() {
        if (m_started)
            End();
        else
            Start();
    }

private:
    CCallbackPaint * m_paint = nullptr;
    bool m_started = false;
    CWnd * m_wnd = nullptr;
};

class CCallbackAnimate : public ICallbackMessage {
public:
    CCallbackAnimate(ICallbackTimer * timer) : m_timer(timer) {}
    virtual ~CCallbackAnimate() {}
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
        m_timer->Toggle();
        return 0;
    }

private:
    ICallbackTimer * m_timer = nullptr;
};

void CControl::AddCallbacks(
    CWnd * wnd
) {
    auto destry = new CCallbackDestroy();
    m_callbacks.push_back(destry);
    wnd->AddCallbackWm(WM_DESTROY, destry);
    auto paint = new CCallbackPaint(wnd);
    m_callbacks.push_back(paint);
    wnd->AddCallbackWm(WM_PAINT, paint);
    auto eraser = new CCallbackErasebkgnd();
    m_callbacks.push_back(eraser);
    wnd->AddCallbackWm(WM_ERASEBKGND, eraser);
    auto about = new CCallbackAbout();
    m_callbacks.push_back(about);
    wnd->AddCallbackCmd(IDM_ABOUT, about);
    auto ext = new CCallbackExit();
    m_callbacks.push_back(ext);
    wnd->AddCallbackCmd(IDM_EXIT, ext);
    CCallbackTimer * tb = new CCallbackTimer(wnd, paint);
    auto anim = new CCallbackAnimate(tb);
    m_callbacks.push_back(anim);
    wnd->AddCallbackCmd(IDM_ANIMATE, anim);
}
