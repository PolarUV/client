#ifndef CLIENT_MAINWINDOW_HPP
#define CLIENT_MAINWINDOW_HPP

#include "Settings/SettingsWindow.hpp"

#include <imgui.h>

namespace App {

class MainWindow {
   public:
    MainWindow();

    ~MainWindow();

    void DrawFrame();

    static void SetupTheme();

   private:
    std::unique_ptr<App::SettingsWindow> settingsWindow_;

    bool settingsWindowOpened_;
};

}  // namespace App

#endif  // CLIENT_MAINWINDOW_HPP
