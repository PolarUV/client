#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintYawIndicator(QPainter &painter, int width, int height, float yawAngle) {

    constexpr const float lineWidth = 4.0f;
    constexpr const float outlineWidth = 1.0f;
    constexpr const float fontSize = 16.0f;
    constexpr const float textOffsetY = 2.0f;
    constexpr const float edgeOffset = 2.0f;

    constexpr const float yawWidth = 800.0f;
    constexpr const float yawHeight = 100.0f;
    constexpr const float centerLineHeight = 10.0f;
    constexpr const float yawBorderOffsetX1 = 0.0f;
    constexpr const float yawBorderOffsetX2 = 20.0f;
    constexpr const float yawBorderOffsetY1 = 45.0f;
    constexpr const float yawBorderOffsetY2 = 65.0f;
    constexpr const float angleRectWidth = 80.0f;
    constexpr const float angleRectHeight = 30.0f;
    constexpr const float valueRectWidth = 60.0f;
    constexpr const float valueRectHeight = 30.0f;
    constexpr const float step = 15.0f;
    constexpr const float distance = 60.0f;

    float textOffsetX;
    if (yawAngle < 10.0f) textOffsetX = 9.0f;
    else if (yawAngle < 100.0f) textOffsetX = 16.0f;
    else textOffsetX = 27.0f;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    painter.save();

    /// Painting angle
    QPainterPath anglePath;
    anglePath.addText((float) width / 2 - textOffsetX,
                      yawHeight - valueRectHeight - 5 + (valueRectHeight + fontSize) / 2 + textOffsetY,
                      font,
                      QString::number((int) yawAngle));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(anglePath);

    /// Painting center value
    QPainterPath centerValuePath;
    auto valueOffset = (float) ((int) yawAngle % (int) step);
    float scaleOffset = (valueOffset * (valueRectWidth + distance)) / step;
    painter.translate((float) width / 2 - scaleOffset, 0);
    float centerValue = yawAngle - valueOffset;
    centerValuePath.addText(-textOffsetX,
                            (yawHeight - yawBorderOffsetY2 + fontSize) / 2 + textOffsetY,
                            font,
                            QString::number((int) centerValue));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(centerValuePath);

    /// Counting indicator borders
    float indicatorRightBorder = ((float) width + yawWidth) / 2;
    float indicatorLeftBorder = ((float) width - yawWidth) / 2;

    /// Painting left values
    float currentX = ((float) width / 2) - scaleOffset;
    int translationNumber = 1;
    while (currentX >= (indicatorLeftBorder + distance + valueRectWidth / 2)) {
        painter.translate(-(valueRectWidth + distance), 0);
        // Checking value
        int value = ((int) (yawAngle - valueOffset) - ((int) step * translationNumber));
        if (value < 0) value = 360 + value;
        else if (value > 360) value = value - 360;
        // Calculating text offset
        int32_t valueOffsetX;
        if (value < 10) valueOffsetX = 9;
        else if (value < 100) valueOffsetX = 16;
        else valueOffsetX = 27;
        // Creating path
        QPainterPath valuePath;
        valuePath.addText(-valueOffsetX,
                          (float) (yawHeight - yawBorderOffsetY2 + fontSize) / 2 + (float) textOffsetY,
                          font,
                          QString::number(value));
        // Painting
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(valuePath);
        //
        translationNumber++;
        currentX -= valueRectWidth + distance;
    }

    /// Translating back to the center
    for (int i = 0; i < translationNumber - 1; i++) {
        painter.translate(valueRectWidth + distance, 0);
        currentX += valueRectWidth + distance;
    }
    translationNumber = 1;

    /// Painting right values
    while (currentX <= (indicatorRightBorder - distance - valueRectWidth / 2)) {
        painter.translate(valueRectWidth + distance, 0);
        // Checking value
        int value = ((int) (yawAngle - valueOffset) + ((int) step * translationNumber));
        if (value < 0) value = 360 - value;
        else if (value == 360) value = 0;
        else if (value > 360) value = value - 360;
        // Calculating text offset
        float valueOffsetX;
        if (value < 10) valueOffsetX = 9.0f;
        else if (value < 100) valueOffsetX = 16.0f;
        else valueOffsetX = 27.0f;
        // Creating path
        QPainterPath valuePath;
        valuePath.addText(-valueOffsetX,
                          (float) (yawHeight - yawBorderOffsetY2 + fontSize) / 2 + textOffsetY,
                          font,
                          QString::number(value));
        // Painting
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(valuePath);
        //
        translationNumber++;
        currentX += valueRectWidth + distance;
    }

    /// Translating back to X = 0
    painter.restore();

    /// Painting the main frame
    QPainterPath framesPath;
    QVector<QPointF> framePolygon = {
            // Outer contour
            QPointF(indicatorLeftBorder + yawBorderOffsetX1,
                    0),
            QPointF(indicatorLeftBorder + yawBorderOffsetX1,
                    yawHeight - yawBorderOffsetY2),
            QPointF(indicatorLeftBorder + yawBorderOffsetX2,
                    yawHeight - yawBorderOffsetY1),
            QPointF(indicatorRightBorder - yawBorderOffsetX2,
                    yawHeight - yawBorderOffsetY1),
            QPointF(indicatorRightBorder - yawBorderOffsetX1,
                    yawHeight - yawBorderOffsetY2),
            QPointF(indicatorRightBorder - yawBorderOffsetX1,
                    0),
            // Inner contour
            QPointF(indicatorRightBorder - yawBorderOffsetX1 - lineWidth,
                    0),
            QPointF(indicatorRightBorder - yawBorderOffsetX1 - lineWidth,
                    yawHeight - yawBorderOffsetY2 - edgeOffset),
            QPointF(indicatorRightBorder - yawBorderOffsetX2 - edgeOffset,
                    yawHeight - yawBorderOffsetY1 - lineWidth),
            QPointF(((float) width + lineWidth) / 2,
                    yawHeight - yawBorderOffsetY1 - lineWidth),
            QPointF(((float) width + lineWidth) / 2,
                    yawHeight - yawBorderOffsetY1 - lineWidth - centerLineHeight),
            QPointF(((float) width - lineWidth) / 2,
                    yawHeight - yawBorderOffsetY1 - lineWidth - centerLineHeight),
            QPointF(((float) width - lineWidth) / 2,
                    yawHeight - yawBorderOffsetY1 - lineWidth),
            QPointF(indicatorLeftBorder + yawBorderOffsetX2 + edgeOffset,
                    yawHeight - yawBorderOffsetY1 - lineWidth),
            QPointF(indicatorLeftBorder + yawBorderOffsetX1 + lineWidth,
                    yawHeight - yawBorderOffsetY2 - edgeOffset),
            QPointF(indicatorLeftBorder + yawBorderOffsetX1 + lineWidth, 0),
    };
    framesPath.addPolygon(QPolygonF(framePolygon));

    /// Painting the angle frame
    QVector<QPointF> angleFramePolygon = {
            // Inner contour
            // 5   1|6   2
            //
            // 4         3
            QPointF((float) width / 2,
                    yawHeight - angleRectHeight - 5),
            QPointF(((float) width + angleRectWidth) / 2,
                    yawHeight - angleRectHeight - 5),
            QPointF(((float) width + angleRectWidth) / 2,
                    yawHeight - 5),
            QPointF(((float) width - angleRectWidth) / 2,
                    yawHeight - 5),
            QPointF(((float) width - angleRectWidth) / 2,
                    yawHeight - angleRectHeight - 5),
            QPointF((float) width / 2,
                    yawHeight - angleRectHeight - 5),
            // Outer contour
            // 2   1|6   5
            //
            // 3         4
            QPointF((float) width / 2,
                    yawHeight - angleRectHeight - 5 - lineWidth),
            QPointF(((float) width - angleRectWidth) / 2 - lineWidth,
                    yawHeight - angleRectHeight - 5 - lineWidth),
            QPointF(((float) width - angleRectWidth) / 2 - lineWidth,
                    yawHeight - 5 + lineWidth),
            QPointF(((float) width + angleRectWidth) / 2 + lineWidth,
                    yawHeight - 5 + lineWidth),
            QPointF(((float) width + angleRectWidth) / 2 + lineWidth,
                    yawHeight - angleRectHeight - 5 - lineWidth),
            QPointF((float) width / 2,
                    yawHeight - angleRectHeight - 5 - lineWidth),
    };
    framesPath.addPolygon(angleFramePolygon);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(framesPath);

    /// Painting the patch to angle frame (hiding polygon outline)
    QPainterPath patchPath;
    patchPath.addRect(((float) width - lineWidth) / 2,
                      yawHeight - angleRectHeight - 5 - lineWidth + outlineWidth,
                      lineWidth,
                      lineWidth - (outlineWidth * 2));

    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(patchPath);
}

