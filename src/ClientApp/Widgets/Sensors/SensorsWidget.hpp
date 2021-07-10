#ifndef CLIENT_SENSORSWIDGET_HPP
#define CLIENT_SENSORSWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QObject>
#include <QTimer>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QOpenGLFramebufferObject>

class SensorsWidget final : public QObject{

    constexpr static int FPS = 30;
    constexpr static auto TIMEOUT_ms = std::chrono::milliseconds( 1000 / FPS);

    Q_OBJECT

public:
    SensorsWidget(QObject* parent, WidgetResources& resources);

public slots:
    void StartWidget();
    void StopWidget();

private slots:
    void ReceiveTelemetry();

public:
    inline SensorsStruct GetSensorsStruct(){
        std::shared_lock lock(sensorsMutex_);
        auto sensors = sensors_;
        return sensors;
    }
private:
    void SetSensorsStruct(const SensorsStruct& sensors);

private:
    std::shared_mutex sensorsMutex_;
    SensorsStruct sensors_;
    WidgetResources& resources_;
    QTimer timer_;
};

#endif
