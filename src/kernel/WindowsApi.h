#pragma once

#include <optional>
#include <windows.h>

class WindowsApi
{
public:
    WindowsApi() = delete;

    static void appendMenu(HMENU popupMenuHandle, long id, const std::string& title);
    
    static HWND createWindow(const std::string& title, const std::string& className, WNDPROC callbackFunction, LPVOID param);
    static HMENU createPopupMenu();

    static NOTIFYICONDATA setupTrayIcon(HWND windowHandle, int iconResourceId);

    static void deleteTrayIcon(NOTIFYICONDATA notifyiconData);
    static POINT getCursorPosisition();
    static void getDesktopResolution(int& horizontal, int& vertical);

    static std::optional<std::string> openSelectFileDialog(const std::string& filter);

private:
    static void throwLastError(const std::string& message);
};
