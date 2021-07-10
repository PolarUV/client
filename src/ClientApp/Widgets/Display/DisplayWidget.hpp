#ifndef CLIENT_DISPLAYWIDGET_HPP
#define CLIENT_DISPLAYWIDGET_HPP

#define WIN32_LEAN_AND_MEAN

#include "../WidgetResources.hpp"
#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include <QMainWindow>
#include <Drawer/Drawer.hpp>

#include "./VideoStream/VideoStream.hpp"
#include "./Screenshotter/Screenshotter.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QOpenGLWidget {
Q_OBJECT

public:
    DisplayWidget(QMainWindow *mainWindow, WidgetResources &resources);

    ~DisplayWidget() override;

private:
    void initializeGL() override;

    void paintGL() override;

    [[maybe_unused]]
    void resizeGL(int w, int h) override;

    static void PaintYawIndicator(QPainter &painter, int width, int height, float yawAngle);

    static void PaintCentralIndicator(QPainter &painter, int width, int height, float rollAngle, float pitchAngle,
                                      float targetRoll, float targetPitch, bool stabilization);

    static void PaintDepthIndicator(QPainter &painter, int width, int height, float currentDepth, float targetDepth,
                                    int valueRange, bool stabilization);

    static void PaintTextInfo(QPainter &painter,
                              int width,
                              int height,
                              std::array<int8_t, 4> calibration,
                              bool stabilizationState,
                              std::array<float, 4> stabilizationTarget);

private:

    Ui::DisplayWidget *ui;

    WidgetResources &resources_;

    lib::processing::VideoStream stream_;

    std::unique_ptr<QTimer> updateTimer_;

    lib::Painter painter_;

    QImage placeholderImage_;

    QImage videoFrame_;

    bool screenshotFlag_;

    ScreenShotter screenshotter_;

public slots:

    void ShowSideBarButton();

    void StopWidget();

    void StartWidget();

private slots:

    void SwitchVideoStream();

    void SwitchVideoCapture();

    void SetScreenshotFlag();

    void HideSideBarButton();

};


#endif
