#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./Widgets/widgets.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QShortcut>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QResizeEvent>

template<class Type>
concept CanRegistryWidget = requires(Type obj){
    obj.StopWidget();
    obj.StartWidget();
} && std::is_convertible_v<Type *, QWidget *>;

template<class Type>
concept CanRegistryObject = requires(Type obj){
    obj.StopWidget();
    obj.StartWidget();
} && std::is_convertible_v<Type *, QObject *>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() final;

protected:

    [[nodiscard]]
    inline AuthorizationWidget *CreateAuthorizationWidget(QWidget *dst) {
        auto widget = new AuthorizationWidget(this);
        dst->layout()->addWidget(widget);
        return widget;
    }

    template<CanRegistryWidget Type, typename ... Args>
    [[nodiscard]]
    inline Type *CreateWidgetWithResources(QWidget *dst, Args &&... args) {
        auto widget = authorizationWidget_->template CreateWithResources<Type>(this, std::forward(args)...);

        dst->layout()->addWidget(widget);

        connect(this, SIGNAL(StartWidget()), widget, SLOT(StartWidget()));
        connect(this, SIGNAL(StopWidget()), widget, SLOT(StopWidget()));

        widget->StopWidget();

        return widget;
    }

    template<typename Type, typename ... Args>
    [[nodiscard]]
    inline Type* CreateWidget(QWidget* dst, Args&& ... args){
        auto widget = new Type(this, std::forward(args)...);
        dst->layout()->addWidget(widget);
        return widget;
    }

    template<CanRegistryObject Type, typename ... Args>
    [[nodiscard]]
    inline Type *CreateObjectWithResources(Args &&... args) {
        auto widget = authorizationWidget_->template CreateWithResources<Type>(this, std::forward(args)...);

        connect(this, SIGNAL(StartWidget()), widget, SLOT(StartWidget()));
        connect(this, SIGNAL(StopWidget()), widget, SLOT(StopWidget()));

        widget->StopWidget();

        return widget;
    }

    void SetupSlots();


public slots:

    void Launch();

    void LaunchDebug();

    void ShowSideBar();

private slots:

    void SwitchToPage1();

    void SwitchToPage2();

    void SwitchToPage2_1();

    void SwitchToPage2_2();

    void SwitchToPage2_3();

    void SwitchToPage2_4();

    void SwitchToPage3();

    void SwitchToPage4();

    void SwitchSideBarButton(int currentIndex);

    void SwitchSideBar();

    void HideSideBar();

    void UpKeyHandler();

    void DownKeyHandler();

    void LeftKeyHandler();

    void RightKeyHandler();

    void SwitchWindowMode();

    void SetWindowedMode();

    void Pause();

signals:

    void StartWidget();

    void StopWidget();

private:

    Ui::MainWindow *ui;

    ///Первым в объявлении всегда должен быть виджет авторизации, поскольку он последним будет уничтожаться
    AuthorizationWidget *authorizationWidget_;
    DisplayWidget *displayWidget_;
    MoveSettingsWidget *moveSettingsWidget_;
    CameraSettingsWidget *cameraSettingsWidget_;
    SensorsSettingsWidget *sensorsSettingsWidget_;
    CommandsSettingsWidget *commandsSettingsWidget_;
    PythonEnvironmentWidget *pythonIDEWidget_;
    SensorsWidget *sensorsObject_;

    bool isDebug_;

    QShortcut *keyF11_;
    QShortcut *keyEsc_;
    QShortcut *keyTab_;
    QShortcut *keyUp_;
    QShortcut *keyDown_;
    QShortcut *keyLeft_;
    QShortcut *keyRight_;
};

#endif

