#include "../DisplayWindow.hpp"
#include "Indicators.hpp"

#include <array>
#include <charconv>
#include <numbers>
#include <vector>

// Число делений шкалы
inline constexpr size_t divisionCount = 6;

void DisplayWindow::PaintDepthIndicator(float scalingFactor, float depth, bool stabilization, float targetDepth,
                                        float maxDepth) {
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
    // Высота шкалы
    const float scaleHeight = 648 * scalingFactor;
    // Размер шрифта
    const float fontSize = 40 * scalingFactor;
    // Расстояние от центра экрана до шкалы
    const float scaleOffset = 320 * scalingFactor;
    // Смещение для создания угла в 45 градусов
    const float edgeOffset = 25 * scalingFactor;
    // Расстояние от деления до подписи
    const float markerOffset = 10 * scalingFactor;
    // Ширина рамки значений углов
    const float valueRectWidth = 80 * scalingFactor;
    // Расстояние между шкалой и маркером стабилизации
    const float pitchStabMarkerOffset = 10 * scalingFactor;

    /// Вторичные параметры

    // Расстояние между делениями шкалы дифферента
    const float divisionHeight = scaleHeight / (divisionCount + 1);
    // Коэффициент перевода глубины в положение маркера
    const float depthToPixelRatio = (divisionCount - 1) / maxDepth * divisionHeight;
    // Координата X значений шкалы дифферента
    const float scaleValuesX = imageCenter.x + scaleOffset + edgeOffset * 2 + markerOffset + valueRectWidth / 2;
    // Координата Y точки отсчета глубины
    const float depthYBase = imageCenter.y - scaleHeight / 2 + divisionHeight;

    /// Преобразование значения глубины

    float depthY = 0;
    if (depth > 0 && depth < maxDepth) {
        depthY = depth * depthToPixelRatio;
    } else if (depth >= maxDepth) {
        depthY = maxDepth * depthToPixelRatio;
    }

    float targetDepthY = 0;
    if (targetDepth > 0 && targetDepth < maxDepth) {
        targetDepthY = targetDepth * depthToPixelRatio;
    } else if (targetDepth >= maxDepth) {
        targetDepthY = maxDepth * depthToPixelRatio;
    }

    /// Создание шкалы

    // Деления шкалы
    for (size_t offset = 1; offset <= divisionCount; offset++) {
        const auto offset_float = static_cast<float>(offset);
        const auto leftVector =
            ImVec2(imageCenter.x + scaleOffset, imageCenter.y - scaleHeight / 2 + divisionHeight * offset_float);
        const auto rightVector = ImVec2(imageCenter.x + scaleOffset + edgeOffset,
                                        imageCenter.y - scaleHeight / 2 + divisionHeight * offset_float);
        drawList->AddLine(leftVector, rightVector, IM_COL32_BLACK, lineWidth + outlineWidth * 2);
        drawList->AddLine(leftVector, rightVector, IM_COL32_WHITE, lineWidth);
    }

    // Маркер текущей глубины
    const std::array pitchMarkerFrame = {
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2.5F + markerOffset + valueRectWidth,
               depthYBase + depthY - edgeOffset / 2),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2.5F + markerOffset + valueRectWidth,
               depthYBase + depthY + edgeOffset / 2),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2 + markerOffset + valueRectWidth,
               depthYBase + depthY + edgeOffset),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2 + markerOffset, depthYBase + depthY + edgeOffset),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset + markerOffset, depthYBase + depthY),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2 + markerOffset, depthYBase + depthY - edgeOffset),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset * 2 + markerOffset + valueRectWidth,
               depthYBase + depthY - edgeOffset),
    };
    drawList->AddPolyline(pitchMarkerFrame.data(), pitchMarkerFrame.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(pitchMarkerFrame.data(), pitchMarkerFrame.size(), IM_COL32_WHITE, ImDrawFlags_Closed,
                          lineWidth);

    // Значение текущей глубины
    std::array<char, 7> depthText{};
    std::to_chars(depthText.data(), depthText.data() + depthText.size(), depth, std::chars_format::fixed, 2);
    const auto depthTextSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, depthText.data());
    const auto pitchPos =
        ImVec2(scaleValuesX - depthTextSize.x / 2, depthYBase + depthY - fontSize / 2 - lineWidth / 2);
    DrawOutlinedText(drawList, pitchPos, depthText.data(), fontSize, outlineWidth);

    // Подписи шкалы
    for (int offset = 0; offset < divisionCount; offset += divisionCount - 1) {
        const auto offset_float = static_cast<float>(offset);
        const float depthValue = maxDepth / 5 * offset_float;

        std::array<char, 7> text{};
        std::to_chars(text.data(), text.data() + text.size(), depthValue, std::chars_format::fixed, 2);
        const auto textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, text.data());

        const float currentValueY = depthYBase + divisionHeight * offset_float - fontSize / 2 - lineWidth / 2;
        const auto pos = ImVec2(scaleValuesX - textSize.x / 2, currentValueY);
        const float depthYRel = depthYBase + depthY - fontSize / 2 - lineWidth / 2;

        if (abs(currentValueY - depthYRel) > divisionHeight / 2 + (5 * scalingFactor)) {
            DrawOutlinedText(drawList, pos, text.data(), fontSize, outlineWidth);
        }
    }

    // Рамка шкалы дифферента
    const std::array depthScaleFrame = {
        ImVec2(imageCenter.x + scaleOffset + edgeOffset, imageCenter.y - scaleHeight / 2),
        ImVec2(imageCenter.x + scaleOffset, imageCenter.y - scaleHeight / 2 + edgeOffset),
        ImVec2(imageCenter.x + scaleOffset, imageCenter.y + scaleHeight / 2 - edgeOffset),
        ImVec2(imageCenter.x + scaleOffset + edgeOffset, imageCenter.y + scaleHeight / 2),
    };
    drawList->AddPolyline(depthScaleFrame.data(), depthScaleFrame.size(), IM_COL32_BLACK, ImDrawFlags_None,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(depthScaleFrame.data(), depthScaleFrame.size(), IM_COL32_WHITE, ImDrawFlags_None, lineWidth);

    /// Создание маркера стабилизации

    if (stabilization) {
        const std::array stabilisationMarker = {
            ImVec2(imageCenter.x + scaleOffset - pitchStabMarkerOffset - edgeOffset / 2,
                   depthYBase + targetDepthY + edgeOffset / 2),
            ImVec2(imageCenter.x + scaleOffset - pitchStabMarkerOffset, depthYBase + targetDepthY),
            ImVec2(imageCenter.x + scaleOffset - pitchStabMarkerOffset - edgeOffset / 2,
                   depthYBase + targetDepthY - edgeOffset / 2),
        };

        drawList->AddPolyline(stabilisationMarker.data(), stabilisationMarker.size(), IM_COL32_BLACK, ImDrawFlags_None,
                              lineWidth + outlineWidth * 2);
        drawList->AddPolyline(stabilisationMarker.data(), stabilisationMarker.size(), IM_COL32_WHITE, ImDrawFlags_None,
                              lineWidth);
    }
}
