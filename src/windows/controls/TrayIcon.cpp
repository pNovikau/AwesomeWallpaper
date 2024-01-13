#include "TrayIcon.h"

#include "windows/Application.h"
#include "resources/resource.h"

TrayIcon::TrayIcon()
{
    _parentWindow = WindowsApi::createWindow("hidden", "HiddenWindowClass", &trayWindowProcStatic, this);
    _data = WindowsApi::setupTrayIcon(_parentWindow, IDI_TRAY_ICON);
}

TrayIcon::~TrayIcon()
{
    WindowsApi::deleteTrayIcon(_data);
}

long TrayIcon::onTrayIconClicked(HWND hwnd) const
{
    const auto hPopupMenu = WindowsApi::createPopupMenu();
    WindowsApi::appendMenu(hPopupMenu, ID_TRAY_MENU_CONFIGURE, "Configure");
    WindowsApi::appendMenu(hPopupMenu, ID_TRAY_MENU_STOP, "Stop");

    const auto [mousePositionX, mousePositionY] = WindowsApi::getCursorPosisition();

    TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, mousePositionX, mousePositionY, 0, hwnd, nullptr);
    DestroyMenu(hPopupMenu);

    return 0;
}

long TrayIcon::onConfigureMenuItemClicked(HWND hwnd) const
{
    auto& application = Application::getInstance();
    application.showConfigurationWindow();

    return 0;
}

long TrayIcon::onStopMenuItemClicked(HWND hwnd) const
{
    MessageBox(hwnd, "Stop Clicked!", "Menu", MB_ICONINFORMATION | MB_OK);

    auto& application = Application::getInstance();
    application.exit();

    return 0;
}

LRESULT CALLBACK TrayIcon::trayWindowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    TrayIcon* trayIcon;

    if (uMsg == WM_NCCREATE)
    {
        trayIcon = static_cast<TrayIcon*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(trayIcon));
    }
    else
    {
        trayIcon = reinterpret_cast<TrayIcon*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    return trayIcon != nullptr
               ? trayIcon->trayWindowProc(hwnd, uMsg, wParam, lParam)
               : DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK TrayIcon::trayWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
{
    if (uMsg == WM_COMMAND)
    {
        const auto itemId = LOWORD(wParam);

        if (itemId == ID_TRAY_MENU_CONFIGURE)
            return onConfigureMenuItemClicked(hwnd);

        if (itemId == ID_TRAY_MENU_STOP)
            return onStopMenuItemClicked(hwnd);
    }
    else if (uMsg == WM_USER + 1)
    {
        if (lParam == WM_RBUTTONUP || lParam == WM_LBUTTONUP)
            return onTrayIconClicked(hwnd);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
