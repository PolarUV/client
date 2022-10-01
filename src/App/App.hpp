#ifndef CLIENT_APP_HPP
#define CLIENT_APP_HPP

#include "Settings/SettingsWindow.hpp"

#include "Renderer/API/BaseWindow.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

class App : public BaseWindow<App> {
   public:
    App() = default;

    ~App() = default;

    void DrawFrameImpl();

    template <class T, typename... Args>
    void AddWindow(Args&&... args) {
        drawer_.template AddWindow<T>(std::forward<Args>(args)...);
    }

   private:
    Drawer drawer_;
};

#endif  // CLIENT_APP_HPP
