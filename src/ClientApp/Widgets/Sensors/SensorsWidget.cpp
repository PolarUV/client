#include "SensorsWidget.hpp"
#include <iostream>

#include <QWindow>

SensorsWidget::SensorsWidget(QObject *parent, WidgetResources &resources) :
        QObject(parent),
        resources_(resources),
        timer_() {

    connect(&timer_, SIGNAL(timeout()), this, SLOT(ReceiveTelemetry()));
}

void SensorsWidget::SetSensorsStruct(const SensorsStruct &sensors) {
    std::unique_lock lock(sensorsMutex_);
    sensors_ = sensors;
}

void SensorsWidget::StartWidget() {
    timer_.start(TIMEOUT_ms);
}

void SensorsWidget::StopWidget() {
    timer_.stop();
}

void SensorsWidget::ReceiveTelemetry() {;
    auto response = resources_.Network.SendReadRequest(1);

    auto sensors = response.DataAs<SensorsStruct>();

    if (sensors) {
        sensors_ = *sensors;
        resources_.Sensors = *sensors;
        return;
    }

    sensors_ = SensorsStruct{};
    resources_.Sensors = SensorsStruct{};
}