#ifndef CLIENT_IWINDOW_HPP
#define CLIENT_IWINDOW_HPP

#include <imgui.h>

#include <memory>
#include <string_view>
#include <vector>

class Drawer;

class IWindow {
    friend Drawer;

   public:
    IWindow(const std::string_view& name, bool isOpened, ImGuiWindowFlags flags)
        : WindowName(name), Flags(flags), IsOpened(isOpened) {}
    virtual void Draw() = 0;
    virtual ~IWindow() = default;

   private:
    const std::string_view WindowName;
    ImGuiWindowFlags Flags;
    bool IsOpened;
};

class Drawer {
   public:
    void operator()() {
        for (auto& window : windows_) {
            ImGui::Begin(window->WindowName.data(), &(window->IsOpened), window->Flags);
            window->Draw();
            ImGui::End();
        }
    }

    template <class T, typename... Args>
    void AddWindow(Args&&... args) {
        std::unique_ptr<IWindow> window = std::make_unique<T>(std::forward<Args>(args)...);
        windows_.push_back(std::move(window));
    }

   private:
    std::vector<std::unique_ptr<IWindow>> windows_;
};

#endif  // CLIENT_IWINDOW_HPP
