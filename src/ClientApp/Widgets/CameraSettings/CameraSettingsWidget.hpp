#ifndef CLIENT_CAMERASETTINGSWIDGET_HPP
#define CLIENT_CAMERASETTINGSWIDGET_HPP

// This must be first include
#include "../WidgetResources.hpp"

#include <QWidget>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class CameraSettingsWidget; }
QT_END_NAMESPACE

class CameraSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit CameraSettingsWidget(QWidget *parent, WidgetResources &resources);

    ~CameraSettingsWidget() override;

public slots:
    void StartWidget();
    void StopWidget();

private:
    void LoadSettings();

    Ui::CameraSettingsWidget *ui;
    WidgetResources& resources_;
    QSettings settings_;

private slots:

    void RefreshClientIPs();

    void UpdateClientIP(const QString& string);

    void RefreshCameraNames();

    void UpdateCameraName(const QString& string);

    void UpdateBrightnessEdit(int value);

    void UpdateBrightnessSlider(const QString& string);

    void UpdateContrastEdit(int value);

    void UpdateContrastSlider(const QString& string);

    void UpdateHueEdit(int value);

    void UpdateHueSlider(const QString& string);

    void UpdateSaturationEdit(int value);

    void UpdateSaturationSlider(const QString& string);

    void UpdateRotatedCheckBox(int state);
};


#endif //CLIENT_CAMERASETTINGSWIDGET_HPP
