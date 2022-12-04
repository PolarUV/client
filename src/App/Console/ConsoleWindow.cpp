#include "ConsoleWindow.hpp"

#include "Logger/Logger.hpp"

constexpr bool isOpened =
#ifdef NDEBUG
    false;
#else
    true;
#endif

ConsoleWindow::ConsoleWindow()
    : IWindow("Отладочная консоль", isOpened, ImGuiWindowFlags_NoCollapse, ImVec2(320, 240)) {}

void ConsoleWindow::Draw() {
    ImGui::TextUnformatted(Logger::GetBuffer().begin(), Logger::GetBuffer().end());

    if (autoScroll_) {
        ImGui::SetScrollHereY(1.0f);
    }
}
