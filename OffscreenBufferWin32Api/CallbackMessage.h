#pragma once

class ICallbackMessage {
public:
    virtual LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;
};
