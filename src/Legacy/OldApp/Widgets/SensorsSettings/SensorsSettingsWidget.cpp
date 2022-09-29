#include "SensorsSettingsWidget.hpp"
#include "ui_SensorsSettingsWidget.h"


SensorsSettingsWidget::SensorsSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::SensorsSettingsWidget),
        resources_(resources){

    ui->setupUi(this);

    connect(ui->ShowIndicatorsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(UpdateIndicatorsState(int)));
    connect(ui->MaxDepthSlider, SIGNAL(valueChanged(int)), this, SLOT(UpdateMaxDepth(int)));
    connect(ui->OrientationSensorOffsetZButton, SIGNAL(pressed()), this, SLOT(UpdateOrientationOffsetZ()));
    connect(ui->DepthCalibrationButton, SIGNAL(pressed()), this, SLOT(UpdateDepthOffset()));
}

SensorsSettingsWidget::~SensorsSettingsWidget() {
    delete ui;
}

void SensorsSettingsWidget::StartWidget() {

}

void SensorsSettingsWidget::StopWidget() {

}

/// ToDo: что-то сделать с этими слотами

void SensorsSettingsWidget::UpdateIndicatorsState(int state) {
    resources_.SensorsSettings.IndicatorsEnabled = (state == Qt::Checked);
}

void SensorsSettingsWidget::UpdateMaxDepth(int value) {
    ui->MaxDepthSlider->setValue(value - (value % ui->MaxDepthSlider->singleStep()));
    ui->MaxDepthEdit->setText(QString::number(value - (value % ui->MaxDepthSlider->singleStep())));

    resources_.SensorsSettings.MaxDepth = value - (value % ui->MaxDepthSlider->singleStep());
}

void SensorsSettingsWidget::UpdateOrientationOffsetZ() {
    resources_.SensorsSettings.OrientationOffsetZ = ui->OrientationSensorOffsetZEdit->text().toFloat();
}

void SensorsSettingsWidget::UpdateDepthOffset() {
    float currentDepth = resources_.Sensors.Depth;
    resources_.SensorsSettings.DepthOffset = currentDepth;
    ui->DepthOffsetEdit->setText(QString::number(currentDepth));
}

