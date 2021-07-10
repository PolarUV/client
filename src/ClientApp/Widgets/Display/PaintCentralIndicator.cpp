#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintCentralIndicator(QPainter &painter, int width, int height, float rollAngle, float pitchAngle,
                                          float targetRoll, float targetPitch, bool stabilization) {

    constexpr const float lineWidth = 4.0f;
    constexpr const float outlineWidth = 1.0f;
    constexpr const float fontSize = 16.0f;
    constexpr const float textOffsetY = 2.0f;
    constexpr const float edgeOffset = 2.0f;

    constexpr const float offsetFromCenter = 378.0f;
    constexpr const float centralHeight = 640.0f;
    constexpr const float horizonLineLength = 320.0f;
    constexpr const float divisionLineLength1 = 160.0f;
    constexpr const float divisionLineLength2 = 80.0f;
    constexpr const float circleRadius = 10.0f;
    constexpr const float centralBorderOffsetY2 = 20.0f;
    constexpr const float centralBorderOffsetX2 = 20.0f;
    constexpr const float horizontalLineLength = 60.0f;
    constexpr const float rectWidth = 110.0f;
    constexpr const float rectHeight = 40.0f;

    /// Converting rollAngle from 0..360 to -180..180
    //rollAngle = (rollAngle <= 180) ? rollAngle : -(rollAngle - 180);
    rollAngle = -(rollAngle - 180);

    float y = pitchAngle;
    if (y < 0) y = 0;
    else if (y > 360) y = 360;
    else if ((0 <= y) && (y < 90)) y = y * 3;
    else if ((90 <= y) && (y < 270)) y = (y - 180) * 3;
    else if ((270 <= y) && (y <= 360)) y = (y - 360) * 3;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    painter.save();
    painter.translate((float) width / 2, (float) height / 2);
    painter.rotate(rollAngle);

    /// Counting indicator borders
    float indicatorRightBorder = (float) width / 2 - offsetFromCenter;
    float indicatorTopBorder = ((float) height - centralHeight) / 2;

    /// Painting the horizon
    QPainterPath horizonPath;
    QVector<QPointF> leftHorizonPolygon{
            QPointF((float) -horizonLineLength / 2,
                    y - (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - (float) lineWidth,
                    y - (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - (float) lineWidth,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) -circleRadius - 5,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) -circleRadius - 5,
                    y + (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - 5,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) -circleRadius - 5 - 5 - 1 - (float) lineWidth,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) -circleRadius - 5 - 1 - (float) lineWidth,
                    y + (float) lineWidth / 2),
            QPointF((float) -horizonLineLength / 2,
                    y + (float) lineWidth / 2),
            QPointF((float) -horizonLineLength / 2,
                    y - (float) lineWidth / 2),
    };
    horizonPath.addPolygon(QPolygonF(leftHorizonPolygon));
    QVector<QPointF> rightHorizonPolygon{
            QPointF((float) horizonLineLength / 2,
                    y - (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + (float) lineWidth,
                    y - (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + (float) lineWidth,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) circleRadius + 5,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) circleRadius + 5,
                    y + (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + 5,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) circleRadius + 5 + 5 + 1 + (float) lineWidth,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) circleRadius + 5 + 1 + (float) lineWidth,
                    y + (float) lineWidth / 2),
            QPointF((float) horizonLineLength / 2,
                    y + (float) lineWidth / 2),
            QPointF((float) horizonLineLength / 2,
                    y - (float) lineWidth / 2),
    };
    horizonPath.addPolygon(QPolygonF(rightHorizonPolygon));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(horizonPath);

    /// Painting upper divisions
    for (auto i = (int) y + 45; i <= 270; i += 45) {
        QPainterPath divisionPath;
        float length = (((((int32_t) y - i) / 45) % 2) == 0) ? divisionLineLength1 : divisionLineLength2;
        QVector<QPointF> leftDivisionPolygon{
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(leftDivisionPolygon));
        QVector<QPointF> rightDivisionPolygon{
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(rightDivisionPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(divisionPath);
    }

    /// Painting lower divisions
    for (auto i = (int32_t) y - 45; i >= -270; i -= 45) {
        QPainterPath divisionPath;
        float length = (((((int32_t) y - i) / 45) % 2) == 0) ? divisionLineLength1 : divisionLineLength2;
        QVector<QPointF> leftDivisionPolygon{
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(leftDivisionPolygon));
        QVector<QPointF> rightDivisionPolygon{
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(rightDivisionPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(divisionPath);
    }

    painter.restore();
    painter.save();

    painter.translate((float) width / 2, (float) height / 2);

    /// Painting the circle
    QPainterPath circlePath;
    circlePath.moveTo(circleRadius, 0);
    circlePath.arcTo(-circleRadius,
                     -circleRadius,
                     circleRadius * 2,
                     circleRadius * 2,
                     0, 360);
    circlePath.moveTo(circleRadius - lineWidth, 0);
    circlePath.arcTo((-circleRadius + lineWidth),
                     (-circleRadius + lineWidth),
                     (circleRadius - lineWidth) * 2,
                     (circleRadius - lineWidth) * 2,
                     0, 360);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(circlePath);

    /// Painting the arc
    QPainterPath arcPath;
    arcPath.moveTo(0, (float) centralHeight / 2 + 5);
    arcPath.arcTo((float) -centralHeight / 2 - 5,
                  (float) -centralHeight / 2 - 5,
                  centralHeight + 10,
                  centralHeight + 10,
                  270,
                  -rollAngle);
    arcPath.arcTo((float) -centralHeight / 2 - 5 - (float) lineWidth,
                  (float) -centralHeight / 2 - 5 - (float) lineWidth,
                  (float) centralHeight + 10 + (float) lineWidth * 2,
                  (float) centralHeight + 10 + (float) lineWidth * 2,
                  270 - rollAngle,
                  rollAngle);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(arcPath);

    painter.restore();
    painter.save();

    painter.translate(0, (float) height / 2);

    /// Painting the marker
    QPainterPath markerPath;
    QVector<QPointF> markerPolygon = {
            QPointF((float) indicatorRightBorder - 30,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10,
                    (float) y - rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y - rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y - rectHeight / 2 + lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - edgeOffset,
                    (float) y - rectHeight / 2 + lineWidth),
            QPointF((float) indicatorRightBorder - 30 - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - edgeOffset,
                    (float) y + rectHeight / 2 - lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y + rectHeight / 2 - lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y + rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10,
                    (float) y + rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30,
                    (float) y)
    };
    markerPath.addPolygon(QPolygonF(markerPolygon));
    // Calculating text offset
    float textOffsetX;
    if (-90 <= (int32_t) (y / 3) && (int32_t) (y / 3) < -9) textOffsetX = 62.0f;       // 4 символа
    else if (0 <= (int32_t) (y / 3) && (int32_t) (y / 3) < 10) textOffsetX = 44.0f;    // 2 символа
    else textOffsetX = 54.0f;                                                          // 3 символа
    //
    markerPath.addText((float) indicatorRightBorder - 30 - 10 - textOffsetX,
                       (float) y + fontSize / 2 + textOffsetY,
                       font,
                       QString::number((int32_t) (y / 3)));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(markerPath);

    /// Painting the patch to marker frame
    QPainterPath patchPath;
    patchPath.addRect((float) indicatorRightBorder - 30 - 10 - rectWidth - 3,
                      (float) y - 1,
                      lineWidth - 2,
                      lineWidth);
    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(patchPath);

    /// Painting the target pitch marker
    if (stabilization) {
        float targetPitchMarkerWidth = 10.0f;
        float targetPitchMarkerY = targetPitch * 3;
        QPainterPath targetPitchMarkerPath;
        QVector<QPointF> targetPitchMarkerPolygon = {
                QPointF(indicatorRightBorder + 5,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10,
                        targetPitchMarkerY - rectHeight / 2),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth + lineWidth,
                        targetPitchMarkerY - rectHeight / 2),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth + lineWidth,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth,
                        targetPitchMarkerY - rectHeight / 2 + lineWidth),
                QPointF(indicatorRightBorder + 5 + 10 + edgeOffset,
                        targetPitchMarkerY - rectHeight / 2 + lineWidth),
                QPointF(indicatorRightBorder + 5 + lineWidth,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10 + edgeOffset,
                        targetPitchMarkerY + rectHeight / 2 - lineWidth),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth,
                        targetPitchMarkerY + rectHeight / 2 - lineWidth),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth + lineWidth,
                        targetPitchMarkerY),
                QPointF(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth + lineWidth,
                        targetPitchMarkerY + rectHeight / 2),
                QPointF(indicatorRightBorder + 5 + 10,
                        targetPitchMarkerY + rectHeight / 2),
                QPointF(indicatorRightBorder + 5,
                        targetPitchMarkerY)
        };
        targetPitchMarkerPath.addPolygon(QPolygonF(targetPitchMarkerPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(targetPitchMarkerPath);

        /// Painting the patch to target pitch marker frame
        QPainterPath targetPitchMarkerPatchPath;
        targetPitchMarkerPatchPath.addRect(indicatorRightBorder + 5 + 10 + targetPitchMarkerWidth + 1,
                                           targetPitchMarkerY - 1,
                                           lineWidth - 2, lineWidth);
        painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(targetPitchMarkerPatchPath);
    }

    /// Painting the scale and its values
    QPainterPath scalePath;
    for (int32_t i = -270; i <= 270; i += 90) {
        scalePath.addRect((float) indicatorRightBorder - 25,
                          (float) i - lineWidth / 2,
                          25,
                          lineWidth);
        // Calculating text offset
        float textOffsetX2;
        if (-90 <= (i / 3) && (i / 3) < -9) textOffsetX2 = 49.0f;       // 4 символа
        else if (0 <= (i / 3) && (i / 3) < 10) textOffsetX2 = 20.0f;    // 2 символа
        else textOffsetX2 = 37.0f;                                      // 3 символа
        //
        if (abs(i - (int32_t) y) >= 45) { // if the marker is far enough
            scalePath.addText((float) indicatorRightBorder - 25 - 10 - textOffsetX2,
                              (float) i + fontSize / 2,
                              font,
                              QString::number(i / 3));
        }
    }
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(scalePath);

    painter.restore();

    /// Painting the frame
    QPainterPath framePath;
    QVector<QPointF> framePolygon = {
            // Outer contour
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    indicatorTopBorder),
            QPointF(indicatorRightBorder - centralBorderOffsetX2,
                    indicatorTopBorder),
            QPointF(indicatorRightBorder,
                    indicatorTopBorder + centralBorderOffsetY2),
            QPointF(indicatorRightBorder,
                    (float) height - indicatorTopBorder - centralBorderOffsetY2),
            QPointF(indicatorRightBorder - centralBorderOffsetX2,
                    (float) height - indicatorTopBorder),
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    (float) height - indicatorTopBorder),
            // Inner contour
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    (float) height - indicatorTopBorder - lineWidth),
            QPointF(indicatorRightBorder - centralBorderOffsetX2 - edgeOffset,
                    (float) height - indicatorTopBorder - lineWidth),
            QPointF(indicatorRightBorder - lineWidth,
                    (float) height - indicatorTopBorder - centralBorderOffsetY2 - edgeOffset),
            QPointF(indicatorRightBorder - lineWidth,
                    indicatorTopBorder + centralBorderOffsetY2 + edgeOffset),
            QPointF(indicatorRightBorder - centralBorderOffsetX2 - edgeOffset,
                    indicatorTopBorder + lineWidth),
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    indicatorTopBorder + lineWidth),
    };
    framePath.addPolygon(QPolygonF(framePolygon));
    framePath.closeSubpath();
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(framePath);

    int32_t offsetX;
    if (rollAngle < -99) offsetX = 34;
    else if ((-99 <= rollAngle && rollAngle < -9) || (100 < rollAngle)) offsetX = 26;
    else if ((-9 <= rollAngle && rollAngle < 0) || (10 <= rollAngle && rollAngle < 100)) offsetX = 18;
    else offsetX = 10;

    /// Painting angle
    QPainterPath rollAnglePath;
    rollAnglePath.addText((float) width / 2 - (float) offsetX,
                          (float) height / 2 + (float) centralHeight / 2 + 45,
                          font,
                          QString::number((int32_t) rollAngle));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAnglePath);

    /// Painting the roll angle frame
    QPainterPath rollAngleFramePath;
    QVector<QPointF> rollAngleFramePolygon = {
            // Inner contour
            // 5   1|6   2
            //
            // 4         3
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15),
            QPointF((float) (width + 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15),
            QPointF((float) (width + 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + 40),
            QPointF((float) (width - 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + 40),
            QPointF((float) (width - 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15),
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15),
            // Outer contour
            // 2   1|6   5
            //
            // 3         4
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + (float) lineWidth),
            QPointF((float) (width - 90) / 2 + (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + (float) lineWidth),
            QPointF((float) (width - 90) / 2 + (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + 40 - (float) lineWidth),
            QPointF((float) (width + 90) / 2 - (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + 40 - (float) lineWidth),
            QPointF((float) (width + 90) / 2 - (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + (float) lineWidth),
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 15 + (float) lineWidth),
    };
    rollAngleFramePath.addPolygon(rollAngleFramePolygon);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAngleFramePath);

    /// Painting the patch to roll angle frame (hiding polygon outline)
    QPainterPath rollAnglePatchPath;
    rollAnglePatchPath.addRect(
            ((float) width - lineWidth) / 2,
            (float) height / 2 + (float) centralHeight / 2 + 15 + (float) outlineWidth,
            lineWidth,
            lineWidth - (outlineWidth * 2));

    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAnglePatchPath);

}

