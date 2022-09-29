#include <QMessageBox>
#include <Exceptions/Exceptions.hpp>
using namespace lib::exceptions;

void ExceptionHandler(const QString &successTitle, const QString &successMessage,  const Function &function) {
    try {
        function();

        if (successTitle != nullptr && successMessage != nullptr)
            QMessageBox::about(nullptr, successTitle, successMessage);

    } catch (const ConnectionException &exception) {
        QMessageBox::warning(nullptr, exception.Error.begin(), exception.Details.begin());
    } catch (const InvalidOperationException &exception) {
        QMessageBox::information(nullptr, exception.Error.begin(), exception.Details.begin());
    } catch (...) {
        QMessageBox::critical(nullptr, "Неизвестная ошибка", "Неизвестная ошибка");
    }
}
