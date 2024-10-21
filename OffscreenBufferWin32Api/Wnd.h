#pragma once

class CApp;

class CWnd {
public:
    CWnd(CApp * app);
    virtual ~CWnd();
    virtual bool Init();
    virtual bool Show(int cmdshow);
    virtual bool Update();

protected:
    virtual ATOM MyRegisterClass();

protected:
    enum {
        MAX_LOADSTRING = 100
    };

    CApp * m_app = nullptr;
    HWND m_hwnd = nullptr;
};
