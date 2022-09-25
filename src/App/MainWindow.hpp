#ifndef CLIENT_MAINWINDOW_HPP
#define CLIENT_MAINWINDOW_HPP

#include "Renderer/API/BaseWindow.h"
#include "Settings/SettingsWindow.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace App {

class MainWindow : public BaseWindow<MainWindow> {
   public:
    MainWindow() = default;

    ~MainWindow() = default;

    void DrawFrameImpl();

    template <class T, typename... Args>
    void AddWindow(Args&&... args) {
        drawer_.template AddWindow<T>(std::forward<Args>(args)...);
    }

   private:
    Drawer drawer_;
};

}  // namespace App

#endif  // CLIENT_MAINWINDOW_HPP
