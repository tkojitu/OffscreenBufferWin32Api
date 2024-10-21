#pragma once

class CWnd;
class ICallbackMessage;

class CControl {
public:
    CControl() {}
    virtual ~CControl() {}
    virtual void AddCallbacks(CWnd * wnd);

private:
    vector<ICallbackMessage*> m_callbacks;

};
