#include "Lib.hpp"

#include "App/MainWindow.hpp"

#include <iostream>

int main() {
    Lib();

    try {
        auto mainWindow = App::MainWindow();
        mainWindow.AddWindow<App::SettingsWindow>();
        mainWindow.Run();
    } catch (std::exception& e) {
        std::cerr << "Some error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::terminate();
    }
    return 0;
}
