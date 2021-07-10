#ifndef CLIENT_SENSORSSETTINGSWIDGET_HPP
#define CLIENT_SENSORSSETTINGSWIDGET_HPP

// This must be first include
#include "../WidgetResources.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SensorsSettingsWidget; }
QT_END_NAMESPACE

class SensorsSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit SensorsSettingsWidget(QWidget *parent, WidgetResources &resources);

    ~SensorsSettingsWidget() override;

public slots:
    void StartWidget();
    void StopWidget();

private:
    Ui::SensorsSettingsWidget *ui;
    WidgetResources& resources_;

private slots:
    void UpdateIndicatorsState(int state);
    void UpdateMaxDepth(int value);
    void UpdateOrientationOffsetZ();
    void UpdateDepthOffset();
};


#endif //CLIENT_SENSORSSETTINGSWIDGET_HPP
