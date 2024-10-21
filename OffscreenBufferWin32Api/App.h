#pragma once

class CApp {
public:
    static CApp * GetApp();

public:
    CApp();
    virtual ~CApp();
    virtual bool InitInstance(HINSTANCE instance, int cmdshow);
    virtual HINSTANCE GetHinstance();

private:
    enum {
        MAX_LOADSTRING = 100
    };

private:
    virtual ATOM MyRegisterClass(HINSTANCE hInstance);

private:
    HINSTANCE m_instance;
    WCHAR m_title[MAX_LOADSTRING] = { 0 };
    WCHAR m_window_class[MAX_LOADSTRING] = { 0 };
};
