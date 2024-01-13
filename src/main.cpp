#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "kernel/WindowsApi.h"
#include "windows/Application.h"
#include "windows/controls/TrayIcon.h"

int main()
{
    auto& application = Application::getInstance();

    application.init();
    application.run();
}
