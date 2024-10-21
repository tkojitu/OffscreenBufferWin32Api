#pragma once

class CControl;
class CWnd;

class CApp {
public:
    static CApp * GetApp();

public:
    CApp();
    virtual ~CApp();
    virtual bool InitInstance(HINSTANCE instance, int cmdshow);
    virtual HINSTANCE GetHinstance();
    virtual int GetIdIcon();
    virtual int GetIdMenu();
    virtual wchar_t * GetTitle();
    virtual wchar_t * GetWindowClass();
    virtual CWnd * GetWnd();

private:
    enum {
        MAX_LOADSTRING = 100
    };

private:
    CControl * m_control = nullptr;
    HINSTANCE m_instance;
    wchar_t m_title[MAX_LOADSTRING] = { 0 };
    wchar_t m_window_class[MAX_LOADSTRING] = { 0 };
    CWnd * m_wnd = nullptr;
};
