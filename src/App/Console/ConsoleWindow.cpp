#include "ConsoleWindow.hpp"

#include "Logger/Logger.hpp"

constexpr bool isOpened =
#ifdef NDEBUG
    false;
#else
    true;
#endif

ConsoleWindow::ConsoleWindow() : IWindow("Debug console", isOpened, ImGuiWindowFlags_NoCollapse) {}

void ConsoleWindow::Draw() {
    ImGui::TextUnformatted(Logger::GetBuffer().begin(), Logger::GetBuffer().end());

    if (autoScroll_) {
        ImGui::SetScrollHereY(1.0f);
    }
}
