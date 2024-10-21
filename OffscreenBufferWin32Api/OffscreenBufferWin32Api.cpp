#include "stdafx.h"
#include "App.h"
#include "OffscreenBufferWin32Api.h"

int APIENTRY wWinMain(
    _In_ HINSTANCE instance,
    _In_opt_ HINSTANCE prev_instance,
    _In_ LPWSTR cmdline,
    _In_ int cmdshow
) {
    if (!CApp::GetApp()->InitInstance(instance, cmdshow)) {
        return 1;
    }
    HACCEL accel = LoadAccelerators(instance, MAKEINTRESOURCE(IDC_OFFSCREENBUFFERWIN32API));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, accel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}
