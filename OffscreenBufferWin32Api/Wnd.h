#pragma once

class CApp;
class ICallbackMessage;
class ICallbackTimer;

class CWnd {
public:
    CWnd(CApp * app);
    virtual ~CWnd();
    virtual void AddCallbackWm(UINT message, ICallbackMessage * callback);
    virtual void AddCallbackCmd(UINT wmid, ICallbackMessage * callback);
    virtual RECT GetClientRect();
    virtual HWND GetHwnd();
    virtual bool Init();
    virtual bool InvalidateRect(RECT rect, bool erase);
    virtual bool KillTimer(ICallbackTimer * callback);
    virtual UINT_PTR SetTimer(ICallbackTimer * callback, UINT elapse);
    virtual bool Show(int cmdshow);
    virtual bool Update();
    virtual LRESULT WindowProcedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

protected:
    virtual ATOM MyRegisterClass();

protected:
    enum {
        MAX_LOADSTRING = 100
    };

    CApp * m_app = nullptr;
    HWND m_hwnd = nullptr;
    map<UINT, ICallbackMessage*> m_callback_cmds;
    map<UINT, ICallbackMessage*> m_callback_wms;
    map<ICallbackTimer*, bool> m_callback_tms;
};
