#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintTextInfo(QPainter &painter,
                                  int width,
                                  int height,
                                  std::array<int8_t, 4> calibration,
                                  bool stabilizationState,
                                  std::array<float, 4> stabilizationTarget) {

    constexpr const float fontSize = 16.0f;
    constexpr const float outlineWidth = 1.0f;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    /// Вывод информации о калибровке
    QPainterPath calibrationPath;
    calibrationPath.addText(10,
                            height - 10,
                            font,
                            QString("Калибровка [%1,%2,%3,%4]").
                                    arg(calibration[0]).
                                    arg(calibration[1]).
                                    arg(calibration[2]).
                                    arg(calibration[3]));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(calibrationPath);

    /// Вывод данных стабилизации
    if (stabilizationState) {
        QPainterPath xTargetPath;
        xTargetPath.addText(width - 240,
                            height - 100,
                            font,
                            QString("X:             %1").
                                    arg((stabilizationTarget[0] < 90.0f) ? stabilizationTarget[0] : 180.0f - stabilizationTarget[0],
                                        0, 'f', 1));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(xTargetPath);

        QPainterPath yTargetPath;
        yTargetPath.addText(width - 240,
                            height - 70,
                            font,
                            QString("Y:             %1").arg(stabilizationTarget[1], 0, 'f', 1));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(yTargetPath);

        QPainterPath zTargetPath;
        zTargetPath.addText(width - 240,
                            height - 40,
                            font,
                            QString("Z:             %1").arg(stabilizationTarget[2], 0, 'f', 1));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(zTargetPath);

        QPainterPath depthTargetPath;
        depthTargetPath.addText(width - 240,
                                height - 10,
                                font,
                                QString("Глубина: %1").arg(stabilizationTarget[3], 0, 'f', 2));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(depthTargetPath);
    }

}