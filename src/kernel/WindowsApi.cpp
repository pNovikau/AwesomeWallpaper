#include <string>
#include <filesystem>

#include "WindowsApi.h"

NOTIFYICONDATA WindowsApi::setupTrayIcon(HWND windowHandle, const int iconResourceId)
{
    NOTIFYICONDATA notifyIconData = {};
    notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
    notifyIconData.hWnd = windowHandle;
    notifyIconData.uID = 1;
    notifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    notifyIconData.uCallbackMessage = WM_USER + 1;
    notifyIconData.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(iconResourceId));
    strcpy_s(notifyIconData.szTip, "Tray Icon Tip");

    if (!Shell_NotifyIcon(NIM_ADD, &notifyIconData))
        throwLastError("Failed to set up tray icon");

    return notifyIconData;
}

void WindowsApi::deleteTrayIcon(NOTIFYICONDATA notifyiconData)
{
    if (!Shell_NotifyIcon(NIM_DELETE, &notifyiconData))
        throwLastError("Failed to delete tray icon");
}

POINT WindowsApi::getCursorPosisition()
{
    POINT point;

    if (!GetCursorPos(&point))
        throwLastError("Failed to delete tray icon");

    return point;
}

void WindowsApi::getDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    
    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

std::optional<std::string> WindowsApi::openSelectFileDialog(const std::string& filter)
{
    OPENFILENAME openFileName = {};
    char szFile[MAX_PATH];

    openFileName.lStructSize = sizeof(openFileName);
    openFileName.hwndOwner = nullptr;
    openFileName.lpstrFile = szFile;
    openFileName.nMaxFile = std::size(szFile);
    openFileName.lpstrFilter = filter.c_str();
    openFileName.nFilterIndex = 1;
    openFileName.lpstrFileTitle = nullptr;
    openFileName.nMaxFileTitle = 0;
    openFileName.lpstrInitialDir = nullptr;
    openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&openFileName))
        return std::string(szFile);

    return std::optional<std::string>();
}

void WindowsApi::throwLastError(const std::string& message)
{
    const auto error = GetLastError();

    throw std::runtime_error(message + " : " + std::to_string(error));
}

HWND WindowsApi::createWindow(const std::string& title, const std::string& className, WNDPROC callbackFunction, LPVOID param)
{
    const auto hInstance = GetModuleHandle(nullptr);

    WNDCLASS wndClass = {};
    wndClass.lpfnWndProc = callbackFunction;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = className.c_str();

    if (!RegisterClass(&wndClass))
        throwLastError("Failed to register window class");

    CREATESTRUCT createStruct = {};
    createStruct.lpCreateParams = param;

    const auto hwnd = CreateWindow(className.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, nullptr, nullptr, hInstance, &createStruct);

    if (!hwnd)
        throwLastError("Failed to create window");

    return hwnd;
}

HMENU WindowsApi::createPopupMenu()
{
    const auto hwnd = CreatePopupMenu();

    if (!hwnd)
        throwLastError("Failed to create popup menu");

    return hwnd;
}

void WindowsApi::appendMenu(HMENU popupMenuHandle, const long id, const std::string& title)
{
    if (!AppendMenu(popupMenuHandle, MF_STRING, id, title.c_str()))
        throwLastError("Failed to create popup menu");
}
