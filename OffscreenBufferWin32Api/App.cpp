#include "stdafx.h"
#include "App.h"
#include "Control.h"
#include "resource.h"
#include "Wnd.h"

CApp * CApp::GetApp(
) {
    static CApp * s_app = nullptr;

    if (s_app)
        return s_app;
    s_app = new CApp();
    return s_app;
}

CApp::CApp(
) {
    m_wnd = new CWnd(this);
    m_control = new CControl();
}

CApp::~CApp(
) {
    delete m_wnd;
}

bool CApp::InitInstance(
    HINSTANCE instance,
    int cmdshow
) {
    m_instance = instance;
    LoadString(instance, IDS_APP_TITLE, m_title, MAX_LOADSTRING);
    LoadString(instance, IDC_OFFSCREENBUFFERWIN32API, m_window_class, MAX_LOADSTRING);
    if (!m_wnd->Init())
        return false;
    m_control->AddCallbacks(m_wnd);
    m_wnd->Show(cmdshow);
    m_wnd->Update();
    return true;
}

HINSTANCE CApp::GetHinstance(
) {
    return m_instance;
}

wchar_t * CApp::GetTitle(
) {
    return m_title;
}

wchar_t * CApp::GetWindowClass(
) {
    return m_window_class;
}

int CApp::GetIdIcon(
) {
    return IDI_OFFSCREENBUFFERWIN32API;
}

int CApp::GetIdMenu(
) {
    return IDC_OFFSCREENBUFFERWIN32API;
}

CWnd * CApp::GetWnd(
) {
    return m_wnd;
}
