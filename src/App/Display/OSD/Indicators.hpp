#ifndef CLIENT_INDICATORS_HPP
#define CLIENT_INDICATORS_HPP

#include <cmath>

#include <array>
#include <numbers>

#include "imgui.h"

inline void DrawOutlinedText(ImDrawList* drawList, ImVec2 pos, const char* text, float fontSize, float outlineWidth) {
    const auto* currentFont = ImGui::GetFont();
    drawList->AddText(currentFont, fontSize, ImVec2(pos.x - outlineWidth, pos.y - outlineWidth), IM_COL32_BLACK, text);
    drawList->AddText(currentFont, fontSize, ImVec2(pos.x - outlineWidth, pos.y + outlineWidth), IM_COL32_BLACK, text);
    drawList->AddText(currentFont, fontSize, ImVec2(pos.x + outlineWidth, pos.y - outlineWidth), IM_COL32_BLACK, text);
    drawList->AddText(currentFont, fontSize, ImVec2(pos.x + outlineWidth, pos.y + outlineWidth), IM_COL32_BLACK, text);
    drawList->AddText(currentFont, fontSize, pos, IM_COL32_WHITE, text);
}

inline ImVec2 RotateVector(const ImVec2& vec, const ImVec2& center, float angleDeg) {
    const float angleRad = angleDeg * std::numbers::pi_v<float> / 180.0F;

    const float sin = std::sin(angleRad);
    const float cos = std::cos(angleRad);

    const ImVec2 localVec = ImVec2(vec.x - center.x, vec.y - center.y);
    const ImVec2 rotatedLocalVec = ImVec2(localVec.x * cos - localVec.y * sin, localVec.x * sin + localVec.y * cos);

    return {rotatedLocalVec.x + center.x, rotatedLocalVec.y + center.y};
}

#endif  // CLIENT_INDICATORS_HPP
