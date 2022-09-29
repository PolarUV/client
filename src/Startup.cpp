#include "Lib.hpp"
#include "Logger/Logger.hpp"

#include "App/App.hpp"

#include <iostream>

int main() {
    Lib();

    try {
        auto app = App();
        app.AddWindow<SettingsWindow>();
        app.AddWindow<ConsoleWindow>();
        app.Run();
    } catch (std::exception& e) {
        PolarError << "Some error occurred: " << e.what();
    } catch (...) {
        std::terminate();
    }
    return 0;
}
