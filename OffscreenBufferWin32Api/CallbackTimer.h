#pragma once

class ICallbackTimer {
public:
    virtual void End() = 0;
    virtual void OnTimer(HWND hwnd, UINT param2, UINT_PTR param3, DWORD param4) = 0;
    virtual void Start() = 0;
    virtual void Toggle() = 0;
};
