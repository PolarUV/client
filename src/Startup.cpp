#include "Lib.hpp"

#include "App/App.hpp"

#include <iostream>

int main() {
    Lib();

    try {
        auto app = App();
        app.AddWindow<SettingsWindow>();
        app.Run();
    } catch (std::exception& e) {
        std::cerr << "Some error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::terminate();
    }
    return 0;
}
