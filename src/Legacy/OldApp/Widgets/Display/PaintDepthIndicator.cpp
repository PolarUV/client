#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintDepthIndicator(QPainter &painter, int width, int height, float currentDepth, float targetDepth,
                                        int valueRange, bool stabilization) {

    constexpr const float lineWidth = 4.0f;
    constexpr const float outlineWidth = 1.0f;
    constexpr const float fontSize = 16.0f;
    constexpr const float textOffsetY = 2.0f;
    constexpr const float edgeOffset = 2.0f;

    constexpr const float depthHeight = 640.0f;
    constexpr const float offsetFromCenter = 378.0f;
    constexpr const float depthBorderOffsetY2 = 20.0f;
    constexpr const float depthBorderOffsetX2 = 20.0f;
    constexpr const float horizontalLineLength = 60.0f;
    constexpr const float depthRectWidth = 110.0f;
    constexpr const float depthRectHeight = 40.0f;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    painter.save();

    /// Counting indicator borders
    float indicatorLeftBorder = (float) width / 2 + offsetFromCenter;
    float indicatorTopBorder = ((float) height - depthHeight) / 2;

    /// Painting the current depth marker
    float currentDepthMarkerY;
    if (currentDepth > (float) valueRange) currentDepthMarkerY = depthHeight / 2 + 270;
    else if (currentDepth < 0) currentDepthMarkerY = (float) depthHeight / 2 - 270;
    else currentDepthMarkerY = ((float) depthHeight / 2 - 270) + (540 * currentDepth / (float) valueRange);
    QPainterPath currentDepthMarkerPath;
    QVector<QPointF> currentDepthMarkerPolygon = {
            QPointF(indicatorLeftBorder + 30,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10,
                    indicatorTopBorder + currentDepthMarkerY - depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + currentDepthMarkerY - depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + currentDepthMarkerY - depthRectHeight / 2 + lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + edgeOffset,
                    indicatorTopBorder + currentDepthMarkerY - depthRectHeight / 2 + lineWidth),
            QPointF(indicatorLeftBorder + 30 + lineWidth,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10 + edgeOffset,
                    indicatorTopBorder + currentDepthMarkerY + depthRectHeight / 2 - lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + currentDepthMarkerY + depthRectHeight / 2 - lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + currentDepthMarkerY),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + currentDepthMarkerY + depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10,
                    indicatorTopBorder + currentDepthMarkerY + depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30,
                    indicatorTopBorder + currentDepthMarkerY)
    };
    currentDepthMarkerPath.addPolygon(QPolygonF(currentDepthMarkerPolygon));
    currentDepthMarkerPath.addText(indicatorLeftBorder + 30 + 10 - 1,
                       indicatorTopBorder + currentDepthMarkerY + fontSize / 2 + textOffsetY,
                       font,
                       QString("%1м").arg(currentDepth, 0, 'f', 2));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(currentDepthMarkerPath);

    /// Painting the patch to current depth marker frame
    QPainterPath currentDepthMarkerPatchPath;
    currentDepthMarkerPatchPath.addRect(indicatorLeftBorder + 30 + 10 + depthRectWidth + 1,
                      indicatorTopBorder + currentDepthMarkerY - 1,
                      lineWidth - 2, lineWidth);
    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(currentDepthMarkerPatchPath);

    /// Painting the current depth marker
    if (stabilization) {
        float targetDepthMarkerWidth = 10.0f;
        float targetDepthMarkerY;
        if (targetDepth > (float) valueRange) targetDepthMarkerY = depthHeight / 2 + 270;
        else if (targetDepth < 0) targetDepthMarkerY = (float) depthHeight / 2 - 270;
        else targetDepthMarkerY = ((float) depthHeight / 2 - 270) + (540 * targetDepth / (float) valueRange);
        QPainterPath targetDepthMarkerPath;
        QVector<QPointF> targetDepthMarkerPolygon = {
                QPointF(indicatorLeftBorder - 5,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10,
                        indicatorTopBorder + targetDepthMarkerY - depthRectHeight / 2),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth - lineWidth,
                        indicatorTopBorder + targetDepthMarkerY - depthRectHeight / 2),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth - lineWidth,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth,
                        indicatorTopBorder + targetDepthMarkerY - depthRectHeight / 2 + lineWidth),
                QPointF(indicatorLeftBorder - 5 - 10 - edgeOffset,
                        indicatorTopBorder + targetDepthMarkerY - depthRectHeight / 2 + lineWidth),
                QPointF(indicatorLeftBorder - 5 - lineWidth,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10 - edgeOffset,
                        indicatorTopBorder + targetDepthMarkerY + depthRectHeight / 2 - lineWidth),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth,
                        indicatorTopBorder + targetDepthMarkerY + depthRectHeight / 2 - lineWidth),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth - lineWidth,
                        indicatorTopBorder + targetDepthMarkerY),
                QPointF(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth - lineWidth,
                        indicatorTopBorder + targetDepthMarkerY + depthRectHeight / 2),
                QPointF(indicatorLeftBorder - 5 - 10,
                        indicatorTopBorder + targetDepthMarkerY + depthRectHeight / 2),
                QPointF(indicatorLeftBorder - 5,
                        indicatorTopBorder + targetDepthMarkerY)
        };
        targetDepthMarkerPath.addPolygon(QPolygonF(targetDepthMarkerPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(targetDepthMarkerPath);

        /// Painting the patch to current depth marker frame
        QPainterPath targetDepthMarkerPatchPath;
        targetDepthMarkerPatchPath.addRect(indicatorLeftBorder - 5 - 10 - targetDepthMarkerWidth - 3,
                                           indicatorTopBorder + targetDepthMarkerY - 1,
                                           lineWidth - 2, lineWidth);
        painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(targetDepthMarkerPatchPath);
    }

    /// Painting the scale and its values
    painter.translate(0, depthHeight / 2);
    int j = 0;
    QPainterPath scalePath;
    for (int i = -270; i <= 270; i += 108) {
        scalePath.addRect(indicatorLeftBorder,
                          indicatorTopBorder + (float) i - lineWidth / 2,
                          25, lineWidth);
        if (abs((depthHeight / 2 + (float) i) - currentDepthMarkerY) >= 45) { // if the marker is far enough
            scalePath.addText(indicatorLeftBorder + 25 + 10,
                              indicatorTopBorder + (float) i + fontSize / 2,
                              font,
                              QString::number(j) + QString("м"));
        }
        j = j + (int) (valueRange / 5);
    }
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(scalePath);

    /// Painting the frame
    painter.restore();
    QPainterPath framePath;
    QVector<QPointF> framePolygon = {
            // Outer contour
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2,
                    indicatorTopBorder),
            QPointF(indicatorLeftBorder,
                    indicatorTopBorder + depthBorderOffsetY2),
            QPointF(indicatorLeftBorder,
                    indicatorTopBorder + depthHeight - depthBorderOffsetY2),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2,
                    indicatorTopBorder + depthHeight),
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + depthHeight),
            // Inner contour
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + depthHeight - lineWidth),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2 + edgeOffset,
                    indicatorTopBorder + depthHeight - lineWidth),
            QPointF(indicatorLeftBorder + lineWidth,
                    indicatorTopBorder + depthHeight - depthBorderOffsetY2 - edgeOffset),
            QPointF(indicatorLeftBorder + lineWidth,
                    indicatorTopBorder + depthBorderOffsetY2 + edgeOffset),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2 + edgeOffset,
                    indicatorTopBorder + lineWidth),
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + lineWidth),
    };
    framePath.addPolygon(QPolygonF(framePolygon));
    framePath.closeSubpath();
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(framePath);
}