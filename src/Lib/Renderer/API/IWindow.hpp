#ifndef CLIENT_IWINDOW_HPP
#define CLIENT_IWINDOW_HPP

#include <imgui.h>

#include <array>
#include <memory>
#include <string_view>
#include <vector>
#include <limits>

class Drawer;

class IWindow {
    friend Drawer;

   public:
    IWindow(const std::string_view& name, bool isOpened, ImGuiWindowFlags flags, ImVec2 size)
        : WindowName(name), Size(size), Flags(flags), IsOpened(isOpened) {}
    virtual void Draw() = 0;
    virtual ~IWindow() = default;

   private:
    const std::string_view WindowName;
    ImVec2 Size;
    ImGuiWindowFlags Flags;
    bool IsOpened;
};

class Drawer {
   public:
    void DrawWindows() {
        for (auto& window : windows_) {
            if (window->IsOpened) {
                ImGui::SetNextWindowSize(ImVec2(window->Size.x, window->Size.y), ImGuiCond_Appearing);
                ImGui::Begin(window->WindowName.data(), &(window->IsOpened), window->Flags);
                window->Draw();
                ImGui::End();
            }
        }
    }

    void DrawWindowsState() {
        if (ImGui::BeginTable("Analog control table", 2)) {
            ImGui::TableSetupColumn("Window name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Window state");

            int index = 0;
            for (auto& window : windows_) {
                ImGui::TableNextColumn();
                ImGui::Text("%s", window->WindowName.data());
                ImGui::TableNextColumn();
                static constexpr auto size = std::numeric_limits<decltype(index)>::digits10 + 2 + 2;
                std::array<char, size> label = {};
                assert(snprintf(label.data(), label.size(), "##%d", index) != -1);
                ImGui::Checkbox(label.data(), &(window->IsOpened));
                index++;
            }

            ImGui::EndTable();
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
