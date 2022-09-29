#include "CameraSettingsWidget.hpp"
#include "ui_CameraSettingsWidget.h"
#include "VideoDevicesMessage.pb.h"

#include "IPFunction.hpp"

using Request = lib::network::Request;
using Response = lib::network::Response;

CameraSettingsWidget::CameraSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::CameraSettingsWidget),
        resources_(resources),
        settings_("NARFU", "PolarUV-Client") {

    ui->setupUi(this);

    /// Загрузка настроек из реестра
    LoadSettings();

    /// Привязка слотов
    connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshClientIPs()));
    connect(ui->ClientIPComboBox, SIGNAL(currentTextChanged(QString)), SLOT(UpdateClientIP(QString)));
    connect(ui->RefreshCameraNamesButton, SIGNAL(clicked(bool)), SLOT(RefreshCameraNames()));
    connect(ui->CameraNameComboBox, SIGNAL(currentTextChanged(QString)), SLOT(UpdateCameraName(QString)));
    connect(ui->BrightnessSlider, SIGNAL(valueChanged(int)), SLOT(UpdateBrightnessEdit(int)));
    connect(ui->BrightnessEdit, SIGNAL(textChanged(QString)), SLOT(UpdateBrightnessSlider(QString)));
    connect(ui->ContrastSlider, SIGNAL(valueChanged(int)), SLOT(UpdateContrastEdit(int)));
    connect(ui->ContrastEdit, SIGNAL(textChanged(QString)), SLOT(UpdateContrastSlider(QString)));
    connect(ui->HueSlider, SIGNAL(valueChanged(int)), SLOT(UpdateHueEdit(int)));
    connect(ui->HueEdit, SIGNAL(textChanged(QString)), SLOT(UpdateHueSlider(QString)));
    connect(ui->SaturationSlider, SIGNAL(valueChanged(int)), SLOT(UpdateSaturationEdit(int)));
    connect(ui->SaturationEdit, SIGNAL(textChanged(QString)), SLOT(UpdateSaturationSlider(QString)));
    connect(ui->RotatedCheckBox, SIGNAL(stateChanged(int)), SLOT(UpdateRotatedCheckBox(int)));
}

CameraSettingsWidget::~CameraSettingsWidget() {
    delete ui;
}

void CameraSettingsWidget::StartWidget() {

}

void CameraSettingsWidget::StopWidget() {

}

void CameraSettingsWidget::LoadSettings() {
    /// Яркость изображения
    if (!settings_.value("CameraBrightness").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.Brightness = settings_.value("CameraBrightness").toInt();
        /// Обновление состояния поля ввода
        ui->BrightnessEdit->setText(settings_.value("CameraBrightness").toString());
        /// Обновление состояния слайдера
        ui->BrightnessSlider->setValue(settings_.value("CameraBrightness").toInt());
    }
    /// Контрастность изображения
    if (!settings_.value("CameraContrast").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.Contrast = settings_.value("CameraContrast").toInt();
        /// Обновление состояния поля ввода
        ui->ContrastEdit->setText(settings_.value("CameraContrast").toString());
        /// Обновление состояния слайдера
        ui->ContrastSlider->setValue(settings_.value("CameraContrast").toInt());
    }
    /// Оттенок изображения
    if (!settings_.value("CameraHue").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.Hue = settings_.value("CameraHue").toInt();
        /// Обновление состояния поля ввода
        ui->HueEdit->setText(settings_.value("CameraHue").toString());
        /// Обновление состояния слайдера
        ui->HueSlider->setValue(settings_.value("CameraHue").toInt());
    }
    /// Насыщенность изображения
    if (!settings_.value("CameraSaturation").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.Saturation = settings_.value("CameraSaturation").toInt();
        /// Обновление состояния поля ввода
        ui->SaturationEdit->setText(settings_.value("CameraSaturation").toString());
        /// Обновление состояния слайдера
        ui->SaturationSlider->setValue(settings_.value("CameraSaturation").toInt());
    }
    /// Переворот изображения
    if (!settings_.value("CameraRotated").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.IsRotated = settings_.value("CameraRotated").toBool();
        /// Обновление состояния чек-бокса
        ui->RotatedCheckBox->setChecked(settings_.value("CameraRotated").toBool());
    }
}

void CameraSettingsWidget::RefreshClientIPs() {
    /// Получение IP-адресов
    auto addresses = GetIps();
    /// Очистка комбо-бокса
    ui->ClientIPComboBox->clear();
    /// Заполнение комбо-бокса
    for (auto &&address: addresses)
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
}

void CameraSettingsWidget::UpdateClientIP(const QString &string) {
    if (string != nullptr) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.ClientIP = string.toStdString();
    }
}

void CameraSettingsWidget::RefreshCameraNames() {
    /// Запрос данных от робота
    auto response = resources_.Network.SendReadRequest(2);
    /// Расшифровка полученных данных
    VideoDeviceMessage message;
    message.ParseFromString(response.Data);
    /// Очистка комбо-бокса
    ui->CameraNameComboBox->clear();
    /// Заполнение комбо-бокса
    for (const auto &device: message.device_names())
        ui->CameraNameComboBox->addItem(device.c_str());

}

void CameraSettingsWidget::UpdateCameraName(const QString &string) {
    if (string != nullptr) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.DeviceName = string.toStdString();
    }
}

void CameraSettingsWidget::UpdateBrightnessEdit(int value) {
    /// Обновление состояния поля ввода
    ui->BrightnessEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.Brightness = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraBrightness", value);
}

void CameraSettingsWidget::UpdateBrightnessSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->BrightnessSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateContrastEdit(int value) {
    /// Обновление состояния поля ввода
    ui->ContrastEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.Contrast = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraContrast", value);
}

void CameraSettingsWidget::UpdateContrastSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->ContrastSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateHueEdit(int value) {
    /// Обновление состояния поля ввода
    ui->HueEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.Hue = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraHue", value);
}

void CameraSettingsWidget::UpdateHueSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->HueSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateSaturationEdit(int value) {
    /// Обновление состояния поля ввода
    ui->SaturationEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.Saturation = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraSaturation", value);
}

void CameraSettingsWidget::UpdateSaturationSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->SaturationSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateRotatedCheckBox(int state) {
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.IsRotated = (state == Qt::Checked);
    /// Обновление переменной в реестре
    settings_.setValue("CameraRotated", (state == Qt::Checked));
}
