#include "../DisplayWindow.hpp"
#include "Indicators.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <numbers>

void DisplayWindow::PaintRollIndicator(float scalingFactor, float roll, float targetRoll, bool stabilization) {
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
    // Суммарная длина левой и правой части линии горизонта
    const float horizonLineLength = 320 * scalingFactor;
    // Размер шрифта
    const float fontSize = 40 * scalingFactor;
    // Радиус вписанной в треугольник окружности
    const float triangleRadius = 5 * scalingFactor;
    // Расстояние до вертикального участка линии горизонта
    const float distance_a = 25 * scalingFactor;
    // Расстояние между линией горизонта и маркером стабилизации
    const float stabilizationMarkerOffset = 30 * scalingFactor;
    // Расстояние от центра экрана до значения угла крена
    const float valueOffset = 324 * scalingFactor;
    // Смещение для создания угла в 45 градусов
    const float edgeOffset = 25 * scalingFactor;
    // Ширина рамки значений углов
    const float valueRectWidth = 80 * scalingFactor;

    /// Вторичные параметры

    // Сторона правильного треугольника
    const float triangleSide = triangleRadius * 2 * std::numbers::sqrt3_v<float>;
    // Толщина наклоненной на 60 градусов линии
    const float inclinedLineWidth = lineWidth * 2 / std::numbers::sqrt3_v<float>;
    // Смещение для обеспечения наклона одной из граней линии на 60 градусов
    const float cornerOffset = lineWidth / (2 * std::numbers::sqrt3_v<float>);
    // Расстояние до горизонтального участка линии горизонта
    const float distance_b = distance_a + triangleRadius + inclinedLineWidth * 1.5F;

    /// Преобразование значений углов

    // Преобразование угла крена из диапазона (0; 360) в диапазон (-180; 180)
    roll = 180 - roll;
    targetRoll = 180 - targetRoll;

    /// Создание центрального маркера

    auto markerBottom = ImVec2(imageCenter.x, imageCenter.y + triangleRadius * 2);
    auto markerRight = ImVec2(imageCenter.x + triangleSide / 2, imageCenter.y - triangleRadius);
    auto markerLeft = ImVec2(imageCenter.x - triangleSide / 2, imageCenter.y - triangleRadius);

    if (!stabilization) {
        drawList->AddTriangle(markerBottom, markerLeft, markerRight, IM_COL32_BLACK, lineWidth + outlineWidth * 2);
        drawList->AddTriangle(markerBottom, markerLeft, markerRight, IM_COL32_WHITE, lineWidth);
    }

    /// Создание линии горизонта

    // Правая половина
    std::array rightHorizonLine = {
        ImVec2(imageCenter.x + horizonLineLength / 2, imageCenter.y - lineWidth / 2),
        ImVec2(imageCenter.x + horizonLineLength / 2, imageCenter.y + lineWidth / 2),
        ImVec2(imageCenter.x + distance_b - cornerOffset, imageCenter.y + lineWidth / 2),
        ImVec2(imageCenter.x + distance_a + inclinedLineWidth, markerBottom.y + lineWidth),
        ImVec2(imageCenter.x + distance_a, markerBottom.y + lineWidth),
        ImVec2(markerRight.x + distance_a + lineWidth, imageCenter.y - triangleRadius - lineWidth / 2),
        ImVec2(markerRight.x + distance_a + lineWidth + inclinedLineWidth,
               imageCenter.y - triangleRadius - lineWidth / 2),
        ImVec2(imageCenter.x + distance_b + cornerOffset, imageCenter.y - lineWidth / 2),
    };
    std::ranges::transform(rightHorizonLine, rightHorizonLine.begin(),
                           [&](auto value) { return RotateVector(value, imageCenter, roll); });

    // Контур
    drawList->AddPolyline(rightHorizonLine.data(), rightHorizonLine.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          outlineWidth * 2);

    // Горизонтальная прямая
    drawList->PathLineTo(rightHorizonLine[0]);
    drawList->PathLineTo(rightHorizonLine[1]);
    drawList->PathLineTo(rightHorizonLine[2]);
    drawList->PathLineTo(rightHorizonLine[7]);
    drawList->PathFillConvex(IM_COL32_WHITE);
    drawList->PathClear();

    // Вертикальная прямая
    for (size_t i = 3; i <= rightHorizonLine.size() - 2; i++) {
        drawList->PathLineTo(rightHorizonLine[i]);
    }
    drawList->PathFillConvex(IM_COL32_WHITE);
    drawList->PathClear();

    // Левая половина
    std::array leftHorizonLine = {
        ImVec2(markerLeft.x - distance_a - lineWidth / 2, markerLeft.y - lineWidth / 2),
        ImVec2(markerBottom.x - distance_a, markerBottom.y + lineWidth),
        ImVec2(markerBottom.x - distance_a - inclinedLineWidth, markerBottom.y + lineWidth),
        ImVec2(imageCenter.x - distance_b + cornerOffset, imageCenter.y + lineWidth / 2),
        ImVec2(imageCenter.x - horizonLineLength / 2, imageCenter.y + lineWidth / 2),
        ImVec2(imageCenter.x - horizonLineLength / 2, imageCenter.y - lineWidth / 2),
        ImVec2(imageCenter.x - distance_b - cornerOffset, imageCenter.y - lineWidth / 2),
        ImVec2(markerLeft.x - distance_a - lineWidth / 2 - inclinedLineWidth, markerLeft.y - lineWidth / 2),
    };
    std::ranges::transform(leftHorizonLine, leftHorizonLine.begin(),
                           [&](auto value) { return RotateVector(value, imageCenter, roll); });

    // Контур
    drawList->AddPolyline(leftHorizonLine.data(), leftHorizonLine.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          outlineWidth * 2);

    // Горизонтальная прямая
    for (size_t i = 3; i <= 6; i++) {
        drawList->PathLineTo(leftHorizonLine[i]);
    }
    drawList->PathFillConvex(IM_COL32_WHITE);
    drawList->PathClear();

    // Вертикальная прямая
    drawList->PathLineTo(leftHorizonLine[0]);
    drawList->PathLineTo(leftHorizonLine[1]);
    drawList->PathLineTo(leftHorizonLine[2]);
    drawList->PathLineTo(leftHorizonLine[7]);
    drawList->PathFillConvex(IM_COL32_WHITE);
    drawList->PathClear();

    /// Создание значения угла крена

    // Значение текущего угла крена
    std::array<char, 5> rollText{};
    std::to_chars(rollText.data(), rollText.data() + rollText.size(), (int)roll);
    const ImVec2 rollTextSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0F, rollText.data());
    const auto rollPos = ImVec2(imageCenter.x - rollTextSize.x / 2,
                                imageCenter.y + valueOffset + edgeOffset - fontSize / 2 - lineWidth / 2);
    DrawOutlinedText(drawList, rollPos, rollText.data(), fontSize, outlineWidth);

    // Рамка
    const std::array rollValueFrame = {
        ImVec2(imageCenter.x + valueRectWidth / 2 + edgeOffset / 2, imageCenter.y + valueOffset + edgeOffset / 2),
        ImVec2(imageCenter.x + valueRectWidth / 2 + edgeOffset / 2, imageCenter.y + valueOffset + edgeOffset * 1.5F),
        ImVec2(imageCenter.x + valueRectWidth / 2, imageCenter.y + valueOffset + edgeOffset * 2),
        ImVec2(imageCenter.x - valueRectWidth / 2, imageCenter.y + valueOffset + edgeOffset * 2),
        ImVec2(imageCenter.x - valueRectWidth / 2 - edgeOffset / 2, imageCenter.y + valueOffset + edgeOffset * 1.5F),
        ImVec2(imageCenter.x - valueRectWidth / 2 - edgeOffset / 2, imageCenter.y + valueOffset + edgeOffset / 2),
        ImVec2(imageCenter.x - valueRectWidth / 2, imageCenter.y + valueOffset),
        ImVec2(imageCenter.x + valueRectWidth / 2, imageCenter.y + valueOffset),
    };
    drawList->AddPolyline(rollValueFrame.data(), rollValueFrame.size(), IM_COL32_BLACK, ImDrawFlags_Closed,
                          lineWidth + outlineWidth * 2);
    drawList->AddPolyline(rollValueFrame.data(), rollValueFrame.size(), IM_COL32_WHITE, ImDrawFlags_Closed, lineWidth);

    /// Создание маркеров стабилизации крена

    if (stabilization) {
        // Левый маркер
        std::array leftRollMarker = {
            ImVec2(imageCenter.x - horizonLineLength / 2 - stabilizationMarkerOffset + triangleRadius * 2,
                   imageCenter.y),
            ImVec2(imageCenter.x - horizonLineLength / 2 - stabilizationMarkerOffset - triangleRadius,
                   imageCenter.y + triangleSide / 2),
            ImVec2(imageCenter.x - horizonLineLength / 2 - stabilizationMarkerOffset - triangleRadius,
                   imageCenter.y - triangleSide / 2),
        };
        std::ranges::transform(leftRollMarker, leftRollMarker.begin(),
                               [&](auto value) { return RotateVector(value, imageCenter, targetRoll); });

        // Правый маркер
        std::array rightRollMarker = {
            ImVec2(imageCenter.x + horizonLineLength / 2 + stabilizationMarkerOffset + triangleRadius,
                   imageCenter.y - triangleSide / 2),
            ImVec2(imageCenter.x + horizonLineLength / 2 + stabilizationMarkerOffset + triangleRadius,
                   imageCenter.y + triangleSide / 2),
            ImVec2(imageCenter.x + horizonLineLength / 2 + stabilizationMarkerOffset - triangleRadius * 2,
                   imageCenter.y),
        };
        std::ranges::transform(rightRollMarker, rightRollMarker.begin(),
                               [&](auto value) { return RotateVector(value, imageCenter, targetRoll); });

        drawList->AddTriangle(leftRollMarker[0], leftRollMarker[1], leftRollMarker[2], IM_COL32_BLACK,
                              lineWidth + outlineWidth * 2);
        drawList->AddTriangle(leftRollMarker[0], leftRollMarker[1], leftRollMarker[2], IM_COL32_WHITE, lineWidth);
        drawList->AddTriangle(rightRollMarker[0], rightRollMarker[1], rightRollMarker[2], IM_COL32_BLACK,
                              lineWidth + outlineWidth * 2);
        drawList->AddTriangle(rightRollMarker[0], rightRollMarker[1], rightRollMarker[2], IM_COL32_WHITE, lineWidth);
    }
}
