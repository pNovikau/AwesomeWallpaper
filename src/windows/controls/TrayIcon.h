#pragma once

#include <string>
#include <memory>

#include "kernel/WindowsApi.h"
#include "SFML/Window.hpp"

class TrayIcon
{
public:
    TrayIcon(const TrayIcon& other) = delete;
    TrayIcon& operator=(const TrayIcon& other) = delete;
    TrayIcon(TrayIcon&& other) = delete;
    TrayIcon& operator=(TrayIcon&& other) = delete;

    TrayIcon();
    ~TrayIcon();

private:
    long onTrayIconClicked(HWND hwnd) const;
    long onConfigureMenuItemClicked(HWND hwnd) const;
    long onStopMenuItemClicked(HWND hwnd) const;

    LRESULT CALLBACK trayWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
    static LRESULT CALLBACK trayWindowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND _parentWindow;
    NOTIFYICONDATA _data{};
};
