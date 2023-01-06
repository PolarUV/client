#include "../DisplayWindow.hpp"
#include "Indicators.hpp"

#include <array>
#include <charconv>
#include <numbers>

// Число делений шкалы
inline constexpr size_t divisionCount = 7;

inline float ConvertPitchAngle(float angleDeg) {
    float convertedAngle = 0;
    if (angleDeg < 0 || angleDeg > 360) {
        convertedAngle = 0;
    } else if ((0 <= angleDeg) && (angleDeg < 90)) {
        convertedAngle = -angleDeg;
    } else if ((90 <= angleDeg) && (angleDeg < 270)) {
        convertedAngle = angleDeg - 180;
    } else if ((270 <= angleDeg) && (angleDeg <= 360)) {
        convertedAngle = 360 - angleDeg;
    }
    return convertedAngle;
}

void DisplayWindow::PaintPitchIndicator(float scalingFactor, float pitch, bool stabilization, float targetPitch) {
    auto* drawList = ImGui::GetWindowDrawList();

    // Нахождение координат центра окна
    const float titleBarHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2;
    const auto imageCenter = ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() / 2,
                                    ImGui::GetWindowPos().y + (ImGui::GetWindowHeight() + titleBarHeight) / 2);

    /// Основные параметры

    // Толщина всех линий без учета толщины контура
    const float lineWidth = 4 * scalingFactor;
    // Толщина контура линий
    const float outlineWidth = 1 * scalingFactor;
    // Высота шкалы дифферента
    const float scaleHeight = 648 * scalingFactor;
    // Размер шрифта
    const float fontSize = 40 * scalingFactor;
    // Расстояние от центра экрана до шкалы дифферента
    const float scaleOffset = 320 * scalingFactor;
    // Смещение для создания угла в 45 градусов
    const float edgeOffset = 25 * scalingFactor;
    // Расстояние от деления до подписи
    const float markerOffset = 10 * scalingFactor;
    // Ширина рамки значений углов
    const float valueRectWidth = 80 * scalingFactor;
    // Расстояние между шкалой дифферента и маркером стабилизации
    const float stabilisationMarkerOffset = 10 * scalingFactor;

    /// Вторичные параметры

    // Расстояние между делениями шкалы дифферента
    const float divisionHeight = scaleHeight / (divisionCount + 1);
    // Коэффициент перевода угла дифферента в положение маркера
    const float pitchToPixelRatio = (scaleHeight - divisionHeight * 2) / (2 * 90);
    // Координата X значений шкалы дифферента
    const float valuesX = imageCenter.x - scaleOffset - edgeOffset * 2 - markerOffset - valueRectWidth / 2;

    /// Преобразование значений углов

    // Преобразование угла дифферента
    const float pitchConverted = ConvertPitchAngle(pitch);
    const float pitchY = pitchConverted * pitchToPixelRatio;

    // Преобразование угла уставки дифферента
    const float targetPitchConverted = ConvertPitchAngle(targetPitch);
    const float targetPitchY = targetPitchConverted * pitchToPixelRatio;

    /// Создание шкалы

    // Деления шкалы
    for (size_t i = 1; i <= divisionCount; i++) {
        const auto leftVector = ImVec2(imageCenter.x - scaleOffset - edgeOffset,
                                       imageCenter.y - scaleHeight / 2 + divisionHeight * (float)i);
        const auto rightVector =
            ImVec2(imageCenter.x - scaleOffset, imageCenter.y - scaleHeight / 2 + divisionHeight * (float)i);
        drawList->AddLine(leftVector, rightVector, IM_COL32_BLACK, lineWidth + outlineWidth * 2);
        drawList->AddLine(leftVector, rightVector, IM_COL32_WHITE, lineWidth);
    }

    // Маркер текущего угла дифферента
    std::array pitchMarkerFrame = {
        ImVec2(imageCenter.x - scaleOffset - edgeOffset - markerOffset, imageCenter.y - pitchY),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2 - markerOffset, imageCenter.y - pitchY + edgeOffset),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2 - markerOffset - valueRectWidth,
               imageCenter.y - pitchY + edgeOffset),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2.5F - markerOffset - valueRectWidth,
               imageCenter.y - pitchY + edgeOffset / 2),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2.5F - markerOffset - valueRectWidth,
               imageCenter.y - pitchY - edgeOffset / 2),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2 - markerOffset - valueRectWidth,
               imageCenter.y - pitchY - edgeOffset),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset * 2 - markerOffset, imageCenter.y - pitchY - edgeOffset),
    };
    drawList->AddPolyline(pitchMarkerFrame.data(), pitchMarkerFrame.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(pitchMarkerFrame.data(), pitchMarkerFrame.size(), IM_COL32_WHITE, ImDrawFlags_Closed,
                          lineWidth);

    // Значение текущего угла дифферента
    std::array<char, 4> pitchText{};
    std::to_chars(pitchText.data(), pitchText.data() + pitchText.size(), (int)pitchConverted);
    const ImVec2 pitchTextSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, pitchText.data());
    const auto pitchPos = ImVec2(valuesX - pitchTextSize.x / 2, imageCenter.y - pitchY - fontSize / 2 - lineWidth / 2);
    DrawOutlinedText(drawList, pitchPos, pitchText.data(), fontSize, outlineWidth);

    // Подписи шкалы
    for (int pitchValue = 90; pitchValue >= -90; pitchValue -= 90) {
        std::array<char, 4> text{};
        std::to_chars(text.data(), text.data() + text.size(), pitchValue);
        const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, text.data());
        const float currentValueY = (float)pitchValue * pitchToPixelRatio;
        const auto pos = ImVec2(valuesX - textSize.x / 2, imageCenter.y - currentValueY - fontSize / 2 - lineWidth / 2);
        if (abs(currentValueY - pitchY) > divisionHeight / 2 + (10 * scalingFactor)) {
            DrawOutlinedText(drawList, pos, text.data(), fontSize, outlineWidth);
        }
    }

    // Рамка шкалы
    const std::array pitchScaleFrame = {
        ImVec2(imageCenter.x - scaleOffset - edgeOffset, imageCenter.y - scaleHeight / 2),
        ImVec2(imageCenter.x - scaleOffset, imageCenter.y - scaleHeight / 2 + edgeOffset),
        ImVec2(imageCenter.x - scaleOffset, imageCenter.y + scaleHeight / 2 - edgeOffset),
        ImVec2(imageCenter.x - scaleOffset - edgeOffset, imageCenter.y + scaleHeight / 2),
    };
    drawList->AddPolyline(pitchScaleFrame.data(), pitchScaleFrame.size(), IM_COL32_BLACK, ImDrawFlags_None,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(pitchScaleFrame.data(), pitchScaleFrame.size(), IM_COL32_WHITE, ImDrawFlags_None, lineWidth);

    /// Создание маркера стабилизации
    if (stabilization) {
        const std::array pitchStabMarker = {
            ImVec2(imageCenter.x - scaleOffset + stabilisationMarkerOffset + edgeOffset / 2,
                   imageCenter.y - targetPitchY + edgeOffset / 2),
            ImVec2(imageCenter.x - scaleOffset + stabilisationMarkerOffset, imageCenter.y - targetPitchY),
            ImVec2(imageCenter.x - scaleOffset + stabilisationMarkerOffset + edgeOffset / 2,
                   imageCenter.y - targetPitchY - edgeOffset / 2),
        };

        drawList->AddPolyline(pitchStabMarker.data(), pitchStabMarker.size(), IM_COL32_BLACK, ImDrawFlags_None,
                              lineWidth + outlineWidth * 2);
        drawList->AddPolyline(pitchStabMarker.data(), pitchStabMarker.size(), IM_COL32_WHITE, ImDrawFlags_None,
                              lineWidth);
    }
}
