#ifndef CLIENT_EXCEPTIONHANDLER_HPP
#define CLIENT_EXCEPTIONHANDLER_HPP

#include <QMessageBox>
#include <functional>

using Function = std::function<void()>;

void ExceptionHandler(const QString &successTitle, const QString &successMessage, const Function &function);

    ///ToDo: доделать универсальный вызыватель функций
//    template<typename Type, typename Signature>
//    //requires std::is_function_v<Function>
//    static void Caller(Type* type, Signature function){
//
//        auto method = Signature([type, function]() { type->function(); });
//        ExceptionHandler(method, nullptr, nullptr);
//
//    }


#endif
