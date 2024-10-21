#pragma once

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

private:
    enum {
        MAX_LOADSTRING = 100
    };

private:
    virtual ATOM MyRegisterClass(HINSTANCE hInstance);

private:
    HINSTANCE m_instance;
    wchar_t m_title[MAX_LOADSTRING] = { 0 };
    wchar_t m_window_class[MAX_LOADSTRING] = { 0 };
    CWnd * m_wnd = nullptr;
};
