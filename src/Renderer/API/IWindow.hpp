#ifndef CLIENT_IWINDOW_HPP
#define CLIENT_IWINDOW_HPP

class IWindow {
   public:
    virtual void Draw(bool* opened) = 0;
    virtual ~IWindow() = default;
};

#endif  // CLIENT_IWINDOW_HPP
