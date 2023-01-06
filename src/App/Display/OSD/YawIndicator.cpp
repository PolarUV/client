#include "../DisplayWindow.hpp"
#include "Indicators.hpp"

#include <array>
#include <charconv>

static constexpr std::array<const char*, 8> cardinalDirections = {"С", "СВ", "В", "ЮВ", "Ю", "ЮЗ", "З", "СЗ"};

void DisplayWindow::PaintYawIndicator(float scalingFactor, float yaw) {
    auto* drawList = ImGui::GetWindowDrawList();

    // Нахождение координат центра окна
    const float titleBarHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2;
    const ImVec2 imageCenter = ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() / 2,
                                      ImGui::GetWindowPos().y + (ImGui::GetWindowHeight() + titleBarHeight) / 2);

    /// Основные параметры

    // Толщина всех линий без учета толщины контура
    const float lineWidth = 4 * scalingFactor;
    // Толщина контура линий
    const float outlineWidth = 1 * scalingFactor;
    // Размер шрифта
    const float fontSize = 40 * scalingFactor;
    // Координата Y верхнего края изображения
    const float imageTop = imageCenter.y - 540 * scalingFactor;
    // Расстояние от центра экрана до значения угла крена
    const float valueOffset = 100 * scalingFactor;
    // Смещение для создания угла в 45 градусов
    const float edgeOffset = 25 * scalingFactor;
    // Ширина рамки значений углов
    const float valueRectWidth = 80 * scalingFactor;
    // Расстояние от верхнего края изображения до шкалы
    const float scaleOffset = 80 * scalingFactor;
    // Ширина шкалы
    const float scaleWidth = 500 * scalingFactor;
    // Расстояние от делений шкалы до значений
    const float scaleTextOffset = 30 * scalingFactor;
    // Расстояние до крайних значений шкалы
    const float cornerValueOffset = 180 * scalingFactor;
    // Коэффициент перевода курса в положение на шкале
    const float yawToPixelRatio = cornerValueOffset / 45;

    /// Отрисовка текущего значения курса

    // Значение
    std::array<char, 4> text{};
    std::to_chars(text.data(), text.data() + text.size(), (int)yaw);
    const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, text.data());
    const auto pos =
        ImVec2(imageCenter.x - textSize.x / 2, imageTop + valueOffset + edgeOffset - fontSize / 2 - lineWidth / 2);
    DrawOutlinedText(drawList, pos, text.data(), fontSize, outlineWidth);

    // Рамка
    const std::array valueFrame = {
        ImVec2(imageCenter.x + valueRectWidth / 2 + edgeOffset / 2, imageTop + valueOffset + edgeOffset / 2),
        ImVec2(imageCenter.x + valueRectWidth / 2 + edgeOffset / 2, imageTop + valueOffset + edgeOffset * 1.5F),
        ImVec2(imageCenter.x + valueRectWidth / 2, imageTop + valueOffset + edgeOffset * 2),
        ImVec2(imageCenter.x - valueRectWidth / 2, imageTop + valueOffset + edgeOffset * 2),
        ImVec2(imageCenter.x - valueRectWidth / 2 - edgeOffset / 2, imageTop + valueOffset + edgeOffset * 1.5F),
        ImVec2(imageCenter.x - valueRectWidth / 2 - edgeOffset / 2, imageTop + valueOffset + edgeOffset / 2),
        ImVec2(imageCenter.x - valueRectWidth / 2, imageTop + valueOffset),
        ImVec2(imageCenter.x + valueRectWidth / 2, imageTop + valueOffset),
    };
    drawList->AddPolyline(valueFrame.data(), valueFrame.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(valueFrame.data(), valueFrame.size(), IM_COL32_WHITE, ImDrawFlags_Closed, lineWidth);

    /// Отрисовка шкалы

    // Центральное деление
    auto topVector = ImVec2(imageCenter.x, imageTop + scaleOffset - edgeOffset);
    auto bottomVector = ImVec2(imageCenter.x, imageTop + scaleOffset);
    drawList->AddLine(topVector, bottomVector, IM_COL32_BLACK, lineWidth + outlineWidth * 2);
    drawList->AddLine(topVector, bottomVector, IM_COL32_WHITE, lineWidth);

    // Шкала
    std::array scaleFrame = {
        ImVec2(imageCenter.x - scaleWidth / 2, imageTop + scaleOffset - edgeOffset),
        ImVec2(imageCenter.x - scaleWidth / 2 + edgeOffset, imageTop + scaleOffset),
        ImVec2(imageCenter.x + scaleWidth / 2 - edgeOffset, imageTop + scaleOffset),
        ImVec2(imageCenter.x + scaleWidth / 2, imageTop + scaleOffset - edgeOffset),
    };
    drawList->AddPolyline(scaleFrame.data(), scaleFrame.size(), IM_COL32_BLACK, ImDrawFlags_None,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(scaleFrame.data(), scaleFrame.size(), IM_COL32_WHITE, ImDrawFlags_None, lineWidth);

    /// Отрисовка значений на шкале

    auto yawConverted = (int)yaw;

    // Центральное значение
    int centralIndex = -1;
    if (yawConverted == 0 || yawConverted == 360) {
        centralIndex = 0;
    } else if (yawConverted % 45 == 0) {
        centralIndex = yawConverted / 45;
    }
    if (centralIndex != -1) {
        const ImVec2 centralTextSize =
            ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, cardinalDirections[centralIndex]);
        const auto centralTextPos = ImVec2(imageCenter.x - centralTextSize.x / 2,
                                           imageTop + scaleOffset - edgeOffset - scaleTextOffset - fontSize / 2);
        DrawOutlinedText(drawList, centralTextPos, cardinalDirections[centralIndex], fontSize, outlineWidth);
    }

    // Левое значение
    int leftIndex;
    float leftOffset;
    if (yawConverted == 0 || yawConverted == 360) {
        leftIndex = 7;
        leftOffset = cornerValueOffset;
    } else if (yawConverted % 45 == 0) {
        leftIndex = yawConverted / 45 - 1;
        leftOffset = cornerValueOffset;
    } else if (0 < yawConverted && yawConverted < 45) {
        leftIndex = 0;
        leftOffset = (float)yawConverted * yawToPixelRatio;
    } else {
        leftIndex = (yawConverted - 45) / 45 + 1;
        leftOffset = (float)(yawConverted % 45) * yawToPixelRatio;
    }
    const ImVec2 leftTextSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, cardinalDirections[leftIndex]);
    const auto leftTextPos = ImVec2(imageCenter.x - leftTextSize.x / 2 - leftOffset,
                                    imageTop + scaleOffset - edgeOffset - scaleTextOffset - fontSize / 2);
    DrawOutlinedText(drawList, leftTextPos, cardinalDirections[leftIndex], fontSize, outlineWidth);

    // Правое значение
    int rightIndex;
    float rightOffset;
    if (yawConverted == 0 || yawConverted == 360) {
        rightIndex = 1;
        rightOffset = cornerValueOffset;
    } else if (315 <= yawConverted && yawConverted < 360) {
        rightIndex = 0;
        rightOffset = (float)(360 - yawConverted) * yawToPixelRatio;
    } else if (0 < yawConverted && yawConverted < 315) {
        rightIndex = (yawConverted + 45) / 45;
        rightOffset = (float)(45 - yawConverted % 45) * yawToPixelRatio;
    }
    const ImVec2 rightTextSize =
        ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, cardinalDirections[rightIndex]);
    const auto rightTextPos = ImVec2(imageCenter.x - rightTextSize.x / 2 + rightOffset,
                                     imageTop + scaleOffset - edgeOffset - scaleTextOffset - fontSize / 2);
    DrawOutlinedText(drawList, rightTextPos, cardinalDirections[rightIndex], fontSize, outlineWidth);
}
